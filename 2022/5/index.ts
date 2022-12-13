import { collectLines } from "../utils.ts";
import {initialStateFromInputLines, operationsFromInputLines, applyOperationToState, applyOperationToState2} from "./supplyStacks.ts";

const input = await collectLines(Deno.stdin.readable);

const operations = operationsFromInputLines(input);
const initialState = initialStateFromInputLines(input);

const resultingState = operations.reduce(applyOperationToState, initialState);
const resultingState2 = operations.reduce(applyOperationToState2, initialState);

function top(state: string[][]): string {
  return state.map(stack => stack.at(-1)).join("");
}

console.log("1)", top(resultingState));
console.log("2)", top(resultingState2));
