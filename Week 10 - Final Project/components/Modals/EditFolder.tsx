import { ModalProps } from '@/types';
import { useState } from 'react';

type EditFolderProps = ModalProps;

export default function EditFolder(Modal: Readonly<EditFolderProps>) {
  const [newName, setNewName] = useState('');
  if (Modal.type != 'Edit Folder') return;
  return (
    <div className='fixed p-5 flex flex-col  z-10 min-w-max max-w-30 min-h-70 overflow-hidden bg-gray-300 text-black border-3 border-primary-red rounded-xl top-1/2 left-1/2 -translate-x-1/2 -translate-y-1/2 md:top-50 md:left-1/2 md:-translate-x-1/2 md:translate-y-0'>
      <h1 className='text-black'>
        {"Do you want to change this folder's name?"}
      </h1>
      <div className='fixed flex flex-col gap-2.5 p-2 bottom-0 md:bottom-10 left-1/2 -translate-y-5 -translate-x-1/2'>
        <form action={Modal.confirm} className='flex flex-col gap-5'>
          <input name='id' type='hidden' value={Modal.id} />

          <label>Change from &rdquo;{Modal.name}&rdquo; to:</label>
          <input
            name='name'
            placeholder='e.g.: Dad'
            autoFocus
            autoComplete='off'
            type='text'
            value={newName}
            onInput={e => setNewName(e.currentTarget.value)}
          />
          <div className='self-end w-full flex justify-between'>
            <button
              className='py-2 px-5 hover:cursor-pointer text-black border-2 border-black bg-white rounded-full'
              onClick={() => Modal.closeModal()}
              type='button'
            >
              Cancel
            </button>
            <button
              className='py-2 px-5 hover:cursor-pointer text-white font-bold  rounded-full bg-red-500 disabled:opacity-50'
              disabled={newName == ''}
              type='submit'
            >
              Save
            </button>
          </div>
        </form>
      </div>
    </div>
  );
}
