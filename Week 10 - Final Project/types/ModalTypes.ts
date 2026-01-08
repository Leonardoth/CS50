import { MedData } from './MedData';

export type ModalType =
  | 'New Med'
  | 'Edit Med'
  | 'New Folder'
  | 'Edit Folder'
  | 'Delete Med'
  | 'Delete Folder'
  | null;

type BaseModal = {
  isOpen: true;
  closeModal: () => void;
};

type ClosedModal = {
  isOpen: false;
  type: 'Closed';
  closeModal: () => void;
};

type NewMed = BaseModal & {
  type: 'New Med';
  confirm: (med: Pick<MedData, 'name' | 'pills' | 'takeAt'>) => void;
};

type EditMed = BaseModal & {
  type: 'Edit Med';
  id: string;
  name: string;
  pills: number;
  takeAt: string[];
  confirm: (med: Pick<MedData, 'id' | 'name' | 'pills' | 'takeAt'>) => void;
};

type DeleteMed = BaseModal & {
  type: 'Delete Med';
  name: string;
  id: string;
  confirm: (id: string) => void;
};

type NewFolder = BaseModal & {
  type: 'New Folder';
  confirm: (formData: FormData) => void;
};

type EditFolder = BaseModal & {
  type: 'Edit Folder';
  id: string;
  name: string;
  confirm: (formData: FormData) => void;
};
type DeleteFolder = BaseModal & {
  type: 'Delete Folder';
  id: string;
  name: string;
  confirm: (id: string) => void;
};

export type ModalProps =
  | ClosedModal
  | NewMed
  | EditMed
  | DeleteMed
  | NewFolder
  | EditFolder
  | DeleteFolder;
