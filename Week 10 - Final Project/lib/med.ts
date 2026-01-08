import { generateID } from '@/lib';
import { Folder, MedData } from '@/types';

export function addMed(
  folders: Folder[],
  folderID: string,
  med: Pick<MedData, 'name' | 'pills' | 'takeAt'>
) {
  return folders.map((folder: Folder) => {
    if (folder.id === folderID) {
      return {
        ...folder,
        items: [
          ...folder.items,
          {
            ...med,
            id: generateID(),
            date: new Date(Date.now()).toISOString(),
          },
        ],
      };
    } else return folder;
  });
}

export function editMed(
  folders: Folder[],
  folderID: string,
  newMed: Pick<MedData, 'id' | 'name' | 'pills' | 'takeAt'>
) {
  return folders.map((folder: Folder) => {
    if (folder.id === folderID) {
      return {
        ...folder,
        items: folder.items.map(med =>
          med.id == newMed.id
            ? {
                ...med,
                ...newMed,
              }
            : med
        ),
      };
    } else return folder;
  });
}
// Filters out the med from the active folder
export function deleteMed(folders: Folder[], folderID: string, itemID: string) {
  return folders.map((folder: Folder) => {
    if (folder.id === folderID) {
      return {
        ...folder,
        items: folder.items.filter(item => item.id !== itemID),
      };
    } else return folder;
  });
}
