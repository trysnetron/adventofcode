
const add = (a: number, b: number): number => a + b;

function segment(arr: string[], size: number): string[][] {
  const res: string[][] = [];
  for (let i = 0; i < arr.length; i += size) {
    res.push(...arr.slice(i, i + size).map(a => Array.from(a)));
  }
  return res;
}

function inAll<T>(listlist: T[][]) {
  const [first, ...rest] = listlist
  let res: T[] = [];
  Array.from(first).forEach(item => {
    if (rest.every(other => other.includes(item)) && !res.includes(item)) {
      res.push(item);
    }
  })
  return res;
}

function charToPriority(char: string): number {
  const code = char.charCodeAt(0)
  return code > 96 ? code - 96 : code - 38;
}

function getRucksackSortPriority(rucksack: string): number {
    const comp1 = rucksack.slice(0, rucksack.length / 2);
    const comp2 = rucksack.slice(rucksack.length / 2);

    const inboth = inAll([Array.from(comp1), Array.from(comp2)])
    
    return inboth
        .map(charToPriority)
        .reduce(add, 0);
}

export function getTotalPriority(rucksacks: string): number {
    return rucksacks
        .split("\n")
        .filter(l => l.length)
        .map(getRucksackSortPriority)
        .reduce(add, 0);
}

export function getTeamPriorities(rucksacks: string): number {
  const all = rucksacks
        .split("\n")
        .filter(l => l.length);

  let res = 0;
  for (let i = 0; i < all.length; i += 3) {

    res += inAll(all.slice(i, i + 3).map(a => Array.from(a))).map(charToPriority).reduce(add, 0);
  }

  return res;
}
