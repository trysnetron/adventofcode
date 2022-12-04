const decoder = new TextDecoder();
let input = "";
for await (const chunk of Deno.stdin.readable) {
  input += decoder.decode(chunk);
}

let completeOverlap = 0;
let someOverlap = 0;
input.split("\n").filter((l) => l.length).forEach((l) => {
  const [a, b] = l.split(",");
  const [a1, a2] = a.split("-").map(Number);
  const [b1, b2] = b.split("-").map(Number);

  if ((a1 >= b1 && a2 <= b2) || (b1 >= a1 && b2 <= a2)) {
    completeOverlap++;
  }
  if ((a1 <= b1 && a2 >= b1) || (a1 >= b1 && a1 <= b2)) {
    someOverlap++;
  }
});

console.log("1)", "n with complete overlap", completeOverlap);
console.log("2)", "n with some overlap", someOverlap);
