
export async function collectLines(stream: ReadableStream): Promise<string[]> {
  const decoder = new TextDecoder();
  let buffer = "";
  for await (const chunk of stream) {
    buffer += decoder.decode(chunk);
  }
  return buffer.split("\n");
}
