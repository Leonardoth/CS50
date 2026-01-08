import { v4 } from 'uuid';

export function generateID() {
  let id = undefined;
  if (typeof globalThis?.crypto?.randomUUID === 'function') {
    id = globalThis.crypto.randomUUID();
  } else {
    id = v4();
  }
  return id;
}
