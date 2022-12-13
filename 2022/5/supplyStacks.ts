

export function initialStateFromInputLines(inputLines: string[]): string[][] {
  const stackNum = inputLines.find(l => l.trim().startsWith("1"))?.replaceAll(" ", "").length;
  if (stackNum === undefined) {
    throw new Error("invalid stacknum")
  }
  const validLines = inputLines.filter(l => l.trim().startsWith("[")).reverse();

  const state = [];
  for (let i = 0; i < stackNum; i++) {
    const newStack = [];
    for (const s of validLines) {
      const c = s.at(1 + i * 4) || " ";
      if (/[A-Z]/.test(c)) {
        newStack.push(c);
      }
    }
    state.push(newStack);
  }
  return state;
}

type Operation = {
  num: number,
  from: number,
  to: number
}

export function operationsFromInputLines(inputLines: string[]): Operation[] {
  return inputLines
    .filter(l => l.startsWith("move"))
    .map(l => {
      const split = l.split(" ");
      return {
        num: Number(split.at(1)),
        from: Number(split.at(3)) - 1,
        to: Number(split.at(5)) - 1
      }
    });
}

export function applyOperationToState(state: string[][], operation: Operation): string[][] {
  const newState = state.map(stack => stack.slice());

  const fromStack = newState.at(operation.from);
  if (fromStack === undefined) {
    throw new Error("Invalid index");
  }

  const toStack = newState.at(operation.to);
  if (toStack === undefined) {
    throw new Error("invalid index");
  }

  const chunk = fromStack.splice(-operation.num);

  if (chunk.length !== operation.num) {
    throw new Error("Invalid length")
  }

  toStack.push(...chunk.reverse());

  return newState;
}

export function applyOperationToState2(state: string[][], operation: Operation): string[][] {
  const newState = state.map(stack => stack.slice());

  const fromStack = newState.at(operation.from);
  if (fromStack === undefined) {
    throw new Error("Invalid index");
  }

  const toStack = newState.at(operation.to);
  if (toStack === undefined) {
    throw new Error("invalid index");
  }

  const chunk = fromStack.splice(-operation.num);

  if (chunk.length !== operation.num) {
    throw new Error("Invalid length")
  }

  toStack.push(...chunk);

  return newState;
}