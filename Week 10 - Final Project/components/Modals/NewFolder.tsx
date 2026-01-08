import { ModalProps } from '@/types';
import { useState } from 'react';

type NewFolderProps = Extract<ModalProps, { type: 'New Folder' }>;

export default function NewFolder({
  confirm,
  closeModal,
}: Readonly<NewFolderProps>) {
  const [newName, setNewName] = useState('');
  return (
    <div className='fixed p-5 flex flex-col top-1/2 left-1/2 -translate-y-1/2 -translate-x-1/2 md:top-0 md:left-0 md:translate-x-1/2 md:translate-y-1/2 z-10 min-w-80 md:min-w-1/2 min-h-1/2 overflow-hidden bg-gray-300 text-black border-3 border-gray-700 rounded-xl'>
      <h1 className='text-black'>Add New Folder</h1>
      <div className='fixed flex flex-col gap-2.5 p-2 bottom-0 md:bottom-10 left-1/2 -translate-y-5 -translate-x-1/2'>
        <form action={confirm}>
          <label aria-label='name'>New Folder Name:</label>
          <input
            name='name'
            placeholder='e.g.: Dad'
            autoComplete='off'
            autoFocus
            type='text'
            value={newName}
            onInput={e => setNewName(e.currentTarget.value)}
          />
          <button
            className='my-2 py-2 px-5 hover:cursor-pointer text-black  rounded-full min-w-full disabled:bg-red-500'
            disabled={newName == ''}
            type='submit'
          >
            Save
          </button>
        </form>

        <button
          className='py-2 px-5 hover:cursor-pointer text-black border-2 border-black bg-white rounded-full min-w-1/3'
          onClick={() => closeModal()}
        >
          Cancel
        </button>
      </div>
    </div>
  );
}
