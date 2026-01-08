import { MedData } from './MedData';

export interface Folder {
  name: string;
  id: string;
  items: MedData[];
}
