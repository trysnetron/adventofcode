
import { assertEquals } from "https://deno.land/std@0.167.0/testing/asserts.ts";
import { initialStateFromInputLines, operationsFromInputLines, applyOperationToState } from "./supplyStacks.ts";

const initialStateInput = `
        [F] [Q]         [Q]        
[B]     [Q] [V] [D]     [S]        
[S] [P] [T] [R] [M]     [D]        
[J] [V] [W] [M] [F]     [J]     [J]
[Z] [G] [S] [W] [N] [D] [R]     [T]
[V] [M] [B] [G] [S] [C] [T] [V] [S]
[D] [S] [L] [J] [L] [G] [G] [F] [R]
[G] [Z] [C] [H] [C] [R] [H] [P] [D]
 1   2   3   4   5   6   7   8   9 `.split("\n");


Deno.test("initial state from input", () => {
    assertEquals(initialStateFromInputLines(initialStateInput),[
      ["G", "D", "V", "Z", "J", "S", "B"],
      ["Z", "S", "M", "G", "V", "P"],
      ["C", "L", "B", "S", "W", "T", "Q", "F"],
      ["H", "J", "G", "W", "M", "R", "V", "Q"],
      ["C", "L", "S", "N", "F", "M", "D"],
      ["R", "G", "C", "D"],
      ["H", "G", "T", "R", "J", "D", "S", "Q"],
      ["P", "F", "V"],
      ["D", "R", "S", "T", "J"]
    ]);
});

Deno.test("ops from input", () => {
  assertEquals(operationsFromInputLines([
    "move 1 from 2 to 3",
    "move 4 from 5 to 6"
  ]), [{num: 1, from: 1, to: 2}, {num: 4, from: 4, to: 5}]);
});

Deno.test("apply op to state", () => {
  assertEquals(applyOperationToState([["A", "B", "C"], ["D"]], {num: 2, from: 0, to: 1}), [["A"], ["D", "C", "B"]]);
})