import { collectStream } from "../utils.ts";
import { findMarker } from "./tuningtrouble.ts";

const input = await collectStream(Deno.stdin.readable);

console.log(input.length);

console.log("1)", findMarker(input, 4));
console.log("2)", findMarker(input, 14));
