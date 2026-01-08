import { ModalProps } from '@/types';
import NewFolder from './Modals/NewFolder';
import DeleteConfirm from './Modals/DeleteConfirm';
import EditFolder from './Modals/EditFolder';
import NewMed from './Modals/NewMed';
import EditMed from './Modals/EditMed';

export function Modal(props: Readonly<ModalProps>) {
  if (!props.isOpen) return;
  switch (props.type) {
    case 'New Med':
      return <NewMed {...props} />;
    case 'Edit Med':
      return <EditMed {...props} />;
    case 'Delete Med':
      return (
        <DeleteConfirm
          {...props}
          ConfirmationText={`Are you sure you want to delete the medication ${props.name}?`}
        />
      );
    case 'New Folder':
      return <NewFolder {...props} />;
    case 'Edit Folder':
      return <EditFolder {...props} />;
    case 'Delete Folder':
      return (
        <DeleteConfirm
          {...props}
          ConfirmationText={`Are you sure you want to delete the folder ${props.name} and all its content?`}
        />
      );
    default:
      return;
  }
}
