import "common"

let square_size (s: square): i32 =
  s.w * s.h

let square_index (w: i32) (s: square) (i: i32): i32 =
  (s.y + i / s.w) * w + s.x + i % s.w

entry answer [n] (xs: [n]i32) (ys: [n]i32) (ws: [n]i32) (hs: [n]i32): i32 =
  let squares = map4 (\x y w h -> {x=x, y=y, w=w, h=h}) xs ys ws hs
  let (w, h) = (reduce_comm i32.max 0 (map (\s -> s.x + s.w) squares),
                reduce_comm i32.max 0 (map (\s -> s.y + s.h) squares))
  let indices = expand square_size (square_index w) squares
  let buffer = reduce_by_index (replicate (w * h) 0) (i32.+) 0 indices (map (const 1) indices)
  let overlaps = map (\k -> if k > 1 then 1 else 0) buffer
  in i32.sum overlaps
