import { Folder, MedData } from '@/types';
import { addDaysLocal, buildLocalDate } from './time';

export function updatePills(lastUpdate: string, folders: Folder[]): Folder[] {
  const updatedFolders = folders.map(folder => ({
    ...folder,
    items: folder.items.map((item: MedData) => {
      const doses = calculateDoses(lastUpdate, item.takeAt);
      return {
        ...item,
        pills: Math.max(item.pills - doses, 0),
      };
    }),
  }));

  return updatedFolders;
}

export function calculateDoses(lastUpdate: string, times: string[]): number {
  const start = new Date(lastUpdate);
  const now = new Date(); // ← use real now -- chatGPT

  // Day cursor starting at the SAME CALENDAR DAY as lastUpdate -- chatGPT
  let dayCursor = new Date(
    start.getFullYear(),
    start.getMonth(),
    start.getDate()
  );

  let doses = 0;

  while (dayCursor <= now) {
    for (const time of times) {
      const doseTime = buildLocalDate(dayCursor, time);
      // Compare using timestamps to avoid timezone drift -- chatGPT

      if (
        doseTime.getTime() > start.getTime() &&
        doseTime.getTime() <= now.getTime()
      ) {
        doses++;
      }
    }
    dayCursor = addDaysLocal(dayCursor, 1);
  }
  return doses;
}
