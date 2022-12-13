export function findMarker(string: string, size: number): number {
  for (let i = 0; i < string.length - size; i++) {
    const test = string.slice(i, i + size);
    if ((new Set(test)).size === size) {
      return i + size;
    }
  }
  throw new Error("no marker available");
}
