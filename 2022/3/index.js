import { getTotalPriority, getTeamPriorities } from "./rucksacks.ts";

const decoder = new TextDecoder();
let input = "";
for await (const chunk of Deno.stdin.readable) {
    input += decoder.decode(chunk);
}

console.log("1)", "Total priority sum", getTotalPriority(input));
console.log("2)", "Team priority sum", getTeamPriorities(input));
