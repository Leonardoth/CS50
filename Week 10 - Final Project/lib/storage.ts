'use client';

import { Folder } from '@/types';

export function saveFolders(folders: Folder[]) {
  localStorage.setItem('folders', JSON.stringify(folders));
}

export function loadFolders(): Folder[] | [] {
  const folders = localStorage.getItem('folders');
  if (!folders) return [];
  return JSON.parse(folders);
}

export function updateLastUpdate() {
  const now = new Date().toISOString();

  localStorage.setItem('lastUpdate', now);
}

export function getLastUpdate(): string | null {
  const lastUpdate = localStorage.getItem('lastUpdate');
  return lastUpdate ? lastUpdate : null;
}
