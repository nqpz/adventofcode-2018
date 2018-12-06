import "common"

type point = {x: i32, y: i32}

let square_points (s: square): []point =
  flatten (map (\x -> map (\y -> {x=x, y=y}) (s.y..<s.y + s.h)) (s.x..<s.x + s.w))

let overlap (s1: square) (s2: square): bool =
  any (\p1 -> any (== p1) (square_points s2)) (square_points s1)

entry answer [n] (xs: [n]i32) (ys: [n]i32) (ws: [n]i32) (hs: [n]i32): i32 =
  let squares = map4 (\x y w h -> {x=x, y=y, w=w, h=h}) xs ys ws hs
  let squares = zip (1..<n + 1) squares
  let checks = map (\(i0, s0) -> (i0, map (\(i1, s1) -> i0 == i1 || ! (overlap s0 s1)) squares)) squares
  let checks = map (\(i, cs) -> if and cs then i else 0) checks
  in i32.sum checks
