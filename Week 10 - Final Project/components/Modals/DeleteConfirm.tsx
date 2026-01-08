import { ModalProps } from '@/types';
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import { faCircleXmark } from '@fortawesome/free-regular-svg-icons';

type DeleteConfirmProps = {
  ConfirmationText: string;
} & (
  | Extract<ModalProps, { type: 'Delete Med' }>
  | Extract<ModalProps, { type: 'Delete Folder' }>
);

export default function DeleteConfirm({
  id,
  confirm,
  closeModal,
  ConfirmationText,
}: Readonly<DeleteConfirmProps>) {
  function submit() {
    confirm(id);
  }

  return (
    <div className='fixed p-5 flex flex-col top-1/2 left-1/2 -translate-y-1/2 -translate-x-1/2 md:top-0 md:-translate-x-1/2 md:translate-y-1/2 z-10 min-w-80 md:min-w-1/2 min-h-1/2 overflow-hidden bg-gray-300 text-black border-3 border-primary-red rounded-xl'>
      <FontAwesomeIcon
        className='self-center text-primary-red'
        icon={faCircleXmark}
        size='4x'
      />
      <h1 className='mt-5 text-black'>{ConfirmationText}</h1>
      <div className='fixed flex flex-col gap-2.5 p-2 bottom-0 left-1/2 -translate-x-1/2'>
        <form action={submit}>
          <input name='id' type='hidden' value={id} />
          <div className='flex justify-between w-100 p-5'>
            <button
              className='py-2 px-5 hover:cursor-pointer text-black border-2 border-black bg-white rounded-full min-w-1/3'
              type='button'
              onClick={() => closeModal()}
            >
              Cancel
            </button>
            <button
              className='py-2 px-5 hover:cursor-pointer text-foreground bg-primary-red rounded-full min-w-1/3'
              type='submit'
            >
              Delete
            </button>
          </div>
        </form>
      </div>
    </div>
  );
}
