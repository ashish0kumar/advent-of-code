package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
	"strconv"
	"strings"
)

type pt struct {
	x, y, z int64
}

type edge struct {
	i, j int
	d    int64
}

func readFile(fname string) []string {
	var lines []string
	f, err := os.Open(fname)
	if err != nil {
		panic(err)
	}
	defer f.Close()

	sc := bufio.NewScanner(f)
	for sc.Scan() {
		lines = append(lines, sc.Text())
	}
	return lines
}

func parse(lines []string) []pt {
	var p []pt
	for _, s := range lines {
		s = strings.TrimSpace(s)
		if s == "" {
			continue
		}
		parts := strings.Split(s, ",")
		if len(parts) != 3 {
			continue
		}
		x, _ := strconv.ParseInt(strings.TrimSpace(parts[0]), 10, 64)
		y, _ := strconv.ParseInt(strings.TrimSpace(parts[1]), 10, 64)
		z, _ := strconv.ParseInt(strings.TrimSpace(parts[2]), 10, 64)
		p = append(p, pt{x, y, z})
	}
	return p
}

func buildEdges(p []pt) []edge {
	n := len(p)
	var es []edge
	for i := 0; i < n; i++ {
		for j := i + 1; j < n; j++ {
			dx := p[i].x - p[j].x
			dy := p[i].y - p[j].y
			dz := p[i].z - p[j].z
			d := dx*dx + dy*dy + dz*dz
			es = append(es, edge{i, j, d})
		}
	}
	sort.Slice(es, func(i, j int) bool {
		return es[i].d < es[j].d
	})
	return es
}

func solve(part2 bool, lines []string) int64 {
	p := parse(lines)
	n := len(p)
	if n == 0 {
		return 0
	}

	es := buildEdges(p)

	par := make([]int, n)
	sz := make([]int64, n)
	for i := 0; i < n; i++ {
		par[i] = i
		sz[i] = 1
	}

	var find func(int) int
	find = func(x int) int {
		for x != par[x] {
			par[x] = par[par[x]]
			x = par[x]
		}
		return x
	}

	union := func(a, b int) bool {
		ra := find(a)
		rb := find(b)
		if ra == rb {
			return false
		}
		if sz[ra] < sz[rb] {
			ra, rb = rb, ra
		}
		par[rb] = ra
		sz[ra] += sz[rb]
		return true
	}

	if !part2 {
		k := 1000
		if k > len(es) {
			k = len(es)
		}

		for i := 0; i < k; i++ {
			e := es[i]
			union(e.i, e.j)
		}

		var comps []int64
		for i := 0; i < n; i++ {
			if par[i] == i {
				comps = append(comps, sz[i])
			}
		}

		if len(comps) < 3 {
			return 0
		}

		sort.Slice(comps, func(i, j int) bool {
			return comps[i] > comps[j]
		})

		return comps[0] * comps[1] * comps[2]
	}

	left := n
	for _, e := range es {
		if union(e.i, e.j) {
			left--
			if left == 1 {
				return p[e.i].x * p[e.j].x
			}
		}
	}

	return 0
}

func main() {
	lines := readFile("input.txt")
	fmt.Println("Part1:", solve(false, lines))
	fmt.Println("Part2:", solve(true, lines))
}