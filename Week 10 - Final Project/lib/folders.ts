import { generateID } from '@/lib';
import { Folder } from '@/types';

export function newFolder(folders: Folder[], name: string) {
  return [...folders, { id: generateID(), name, items: [] }];
}

export function deleteFolder(folders: Folder[], id: string) {
  return folders.filter(folder => folder.id !== id);
}

export function renameFolder(folders: Folder[], id: string, newName: string) {
  return folders.map(folder =>
    folder.id == id ? { ...folder, name: newName } : folder
  );
}
