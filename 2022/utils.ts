
export async function collectStream(stream: ReadableStream): Promise<string> {
  const decoder = new TextDecoder();
  let buffer = "";
  for await (const chunk of stream) {
    buffer += decoder.decode(chunk);
  }
  return buffer;
}

export async function collectLines(stream: ReadableStream): Promise<string[]> {
  return (await collectStream(stream)).split("\n");
}
