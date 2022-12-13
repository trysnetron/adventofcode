import { assertEquals } from "https://deno.land/std@0.167.0/testing/asserts.ts";
import { findMarker } from "./tuningtrouble.ts";

Deno.test("example", () => {
  assertEquals(findMarker("mjqjpqmgbljsphdztnvjfqwrcgsmlb", 4), 7);
});
