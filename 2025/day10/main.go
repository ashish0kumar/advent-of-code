package main

import (
	"bufio"
	"fmt"
	"os"
	"os/exec"
	"strconv"
	"strings"
)

type lamps []int
type pzl struct {
	sw [][]int
	j  []int
}

func readFile(fn string) []string {
	f, err := os.Open(fn)
	if err != nil {
		panic(err)
	}
	defer f.Close()

	var out []string
	sc := bufio.NewScanner(f)
	for sc.Scan() {
		out = append(out, sc.Text())
	}
	return out
}

func apply(s lamps, idx int, sw [][]int) lamps {
	n := make(lamps, len(s))
	copy(n, s)
	for _, v := range sw[idx] {
		if v < len(n) {
			n[v] = 1 - n[v]
		}
	}
	return n
}

func key(s lamps) string { 
	return fmt.Sprint(s) 
}

func bfs(n int, sw [][]int, tgt lamps) ([]int, int) {
	start := make(lamps, n)
	seen := map[string]bool{key(start): true}
	type node struct {
		s lamps
		p []int
	}

	q := []node{{start, nil}}
	for len(q) > 0 {
		cur := q[0]
		q = q[1:]
		if key(cur.s) == key(tgt) {
			return cur.p, len(cur.p)
		}

		for i := 0; i < len(sw); i++ {
			ns := apply(cur.s, i, sw)
			k := key(ns)
			if !seen[k] {
				seen[k] = true
				np := append(append([]int(nil), cur.p...), i)
				q = append(q, node{ns, np})
			}
		}
	}
	return nil, int(^uint(0) >> 1)
}

func parseLine(l string) (*pzl, error) {
	f := strings.Fields(l)
	if len(f) < 2 {
		return nil, fmt.Errorf("bad line")
	}

	swT := f[1 : len(f)-1]
	jT := strings.Trim(f[len(f)-1], "{}")

	var sw [][]int
	for _, s := range swT {
		s = strings.Trim(s, "()")
		if s == "" {
			sw = append(sw, nil)
			continue
		}
		parts := strings.Split(s, ",")
		var cur []int
		for _, p := range parts {
			p = strings.TrimSpace(p)
			v, err := strconv.Atoi(p)
			if err != nil {
				return nil, err
			}
			cur = append(cur, v)
		}
		sw = append(sw, cur)
	}

	var j []int
	if jT != "" {
		for _, p := range strings.Split(jT, ",") {
			p = strings.TrimSpace(p)
			v, err := strconv.Atoi(p)
			if err != nil {
				return nil, err
			}
			j = append(j, v)
		}
	}

	return &pzl{sw: sw, j: j}, nil
}

func genLP(p *pzl, fn string) {
	f, err := os.Create(fn)
	if err != nil {
		panic(err)
	}
	defer f.Close()

	fmt.Fprintln(f, "Minimize")
	fmt.Fprint(f, "obj:")
	for i := range p.sw {
		fmt.Fprintf(f, " + x%d", i+1)
	}

	fmt.Fprintln(f, "\n\nSubject To")
	for j := 0; j < len(p.j); j++ {
		fmt.Fprintf(f, "c%d: ", j+1)
		first := true
		for i, inter := range p.sw {
			if contains(inter, j) {
				if !first {
					fmt.Fprint(f, " + ")
				}
				fmt.Fprintf(f, "x%d", i+1)
				first = false
			}
		}
		fmt.Fprintf(f, " = %d\n", p.j[j])
	}

	fmt.Fprintln(f, "\nBounds")
	for i := range p.sw {
		fmt.Fprintf(f, "x%d >= 0\n", i+1)
	}

	fmt.Fprintln(f, "\nGenerals")
	for i := range p.sw {
		fmt.Fprintf(f, "x%d\n", i+1)
	}

	fmt.Fprintln(f, "End")
}

func contains(a []int, v int) bool {
	for _, x := range a {
		if x == v {
			return true
		}
	}
	return false
}

func solveGLP(fn string) int {
	cmd := exec.Command("glpsol", "--lp", fn, "--output", "solution.txt")
	if err := cmd.Run(); err != nil {
		panic(err)
	}
	data, err := os.ReadFile("solution.txt")
	if err != nil {
		panic(err)
	}

	for _, l := range strings.Split(string(data), "\n") {
		if strings.Contains(l, "Objective:") {
			f := strings.Fields(l)
			if len(f) >= 4 {
				v, err := strconv.Atoi(f[3])
				if err != nil {
					panic(err)
				}
				return v
			}
		}
	}
	panic("objective not found")
}

func solve(part2 bool, lines []string) int {
	if !part2 {
		s := 0
		for _, ln := range lines {
			parts := strings.Fields(ln)
			if len(parts) == 0 {
				continue
			}

			t := strings.Trim(parts[0], "[]")
			tg := make(lamps, len(t))
			for i, c := range t {
				if c == '#' {
					tg[i] = 1
				}
			}

			sw := parts[1 : len(parts)-1]
			var swv [][]int
			for _, st := range sw {
				st = strings.Trim(st, "()")
				if st == "" {
					swv = append(swv, nil)
					continue
				}
				ps := strings.Split(st, ",")
				var cur []int

				for _, p := range ps {
					p = strings.TrimSpace(p)
					v, _ := strconv.Atoi(p)
					cur = append(cur, v)
				}
				swv = append(swv, cur)
			}
			
			_, r := bfs(len(tg), swv, tg)
			// fmt.Println(tg, ":", r, "(", swv, ")")
			s += r
		}
		return s
	}

	sum := 0
	for _, ln := range lines {
		p, err := parseLine(ln)
		if err != nil {
			continue
		}
		genLP(p, "jolt.lp")
		v := solveGLP("jolt.lp")
		sum += v
	}
	return sum
}

func main() {
	lines := readFile("input.txt")
	fmt.Println("Part1:", solve(false, lines))
	fmt.Println("Part2:", solve(true, lines))
}