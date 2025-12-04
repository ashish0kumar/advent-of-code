package main

import (
	"bufio"
	"fmt"
	"os"
)

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

func adjCnt(g [][]byte, i, j, h, w int) int {
	c := 0
	for di := -1; di <= 1; di++ {
		for dj := -1; dj <= 1; dj++ {
			if di == 0 && dj == 0 {
				continue
			}
			ni := i + di
			nj := j + dj
			if ni < 0 || ni >= h || nj < 0 || nj >= w {
				continue
			}
			if g[ni][nj] == '@' {
				c++
			}
		}
	}
	return c
}

func solve(part2 bool, in []string) int64 {
	h := len(in)
	if h == 0 {
		return 0
	}
	w := len(in[0])

	if !part2 {
		var res int64
		g := make([][]byte, h)
		for i := 0; i < h; i++ {
			g[i] = []byte(in[i])
		}
		for i := 0; i < h; i++ {
			for j := 0; j < w; j++ {
				if g[i][j] != '@' {
					continue
				}
				if adjCnt(g, i, j, h, w) < 4 {
					res++
				}
			}
		}
		return res
	}

	g := make([][]byte, h)
	for i := 0; i < h; i++ {
		g[i] = []byte(in[i])
	}

	var total int64

	for {
		type p struct{ i, j int }
		var rem []p

		for i := 0; i < h; i++ {
			for j := 0; j < w; j++ {
				if g[i][j] != '@' {
					continue
				}
				if adjCnt(g, i, j, h, w) < 4 {
					rem = append(rem, p{i, j})
				}
			}
		}

		if len(rem) == 0 {
			break
		}

		for _, x := range rem {
			g[x.i][x.j] = '.'
		}
		total += int64(len(rem))
	}

	return total
}

func main() {
	lines := readFile("input.txt")
	fmt.Println("Part1:", solve(false, lines))
	fmt.Println("Part2:", solve(true, lines))
}