'use client';
import Meds from '../components/Meds';
import { Folder, ModalProps, MedData } from '@/types';
import { useEffect, useState } from 'react';
import { Modal } from '@/components/Modal';
import {
  deleteFolder,
  newFolder,
  renameFolder,
  deleteMed,
  addMed,
  editMed,
  updatePills,
} from '@/lib';

// Icons component
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
// solid icons
import {
  faFolderClosed,
  faPills,
  faFolderPlus,
} from '@fortawesome/free-solid-svg-icons';
// regular icons
import {
  faPenToSquare,
  faTrashAlt,
  faFolderOpen,
} from '@fortawesome/free-regular-svg-icons';
import {
  getLastUpdate,
  loadFolders,
  saveFolders,
  updateLastUpdate,
} from '@/lib/storage';

const initialModal: ModalProps = {
  isOpen: false,
  type: 'Closed',
  closeModal: () => {},
};

export default function Home() {
  const [folders, setFolders] = useState<Folder[]>([]);
  const [activeFolder, setActiveFolder] = useState(0);
  const [modalData, setModalData] = useState<ModalProps>(initialModal);

  useEffect(() => {
    let savedFolders = loadFolders();
    const lastUpdate = getLastUpdate();
    if (!lastUpdate) {
      // eslint-disable-next-line react-hooks/set-state-in-effect
      setFolders(savedFolders);
      updateLastUpdate();
    } else {
      savedFolders = updatePills(lastUpdate, savedFolders);
      setFolders(savedFolders);
      updateLastUpdate();
    }
  }, []);

  useEffect(() => {
    if (modalData.isOpen) {
      document.body.classList.add('overflow-y-hidden');
    } else {
      document.body.classList.remove('overflow-y-hidden');
    }
  }, [modalData.isOpen]);

  useEffect(() => {
    saveFolders(folders);
  }, [folders]);

  function openAddFolder() {
    setModalData({
      ...modalData,
      isOpen: true,
      type: 'New Folder',
      confirm: handleAddFolder,
    });
  }

  function openAddMed() {
    setModalData({
      ...modalData,
      isOpen: true,
      type: 'New Med',
      confirm: handleAddMed,
    });
  }

  function openDeleteFolder() {
    setModalData({
      ...modalData,
      isOpen: true,
      type: 'Delete Folder',
      name: folders[activeFolder].name,
      id: folders[activeFolder].id,
      confirm: handleDeleteFolder,
    });
  }
  function openEditFolder() {
    setModalData({
      ...modalData,
      isOpen: true,
      type: 'Edit Folder',
      name: folders[activeFolder].name,
      id: folders[activeFolder].id,
      confirm: handleRenameFolder,
    });
  }
  function handleAddFolder(formData: FormData) {
    const name = formData.get('name') as string;
    setFolders(prev => newFolder(prev, name));
    changeFolder(0);
    closeModal();
  }
  function handleRenameFolder(formData: FormData) {
    const newName = formData.get('name') as string;
    const id = formData.get('id') as string;
    setFolders(prev => renameFolder(prev, id, newName));
    closeModal();
  }
  function handleDeleteFolder(id: string) {
    setFolders(prev => deleteFolder(prev, id));
    changeFolder(0);
    closeModal();
  }

  function handleAddMed({
    name,
    pills,
    takeAt,
  }: Pick<MedData, 'name' | 'pills' | 'takeAt'>) {
    setFolders(folders =>
      addMed(folders, folders[activeFolder].id, { name, pills, takeAt })
    );
    closeModal();
  }
  function handleEditMed({
    id,
    name,
    pills,
    takeAt,
  }: Pick<MedData, 'id' | 'name' | 'pills' | 'takeAt'>) {
    setFolders(folders =>
      editMed(folders, folders[activeFolder].id, { id, name, pills, takeAt })
    );
    closeModal();
  }

  function handleDeleteMed(id: string) {
    setFolders(folders => deleteMed(folders, folders[activeFolder].id, id));
    closeModal();
  }

  function closeModal() {
    setModalData(initialModal);
  }

  function changeFolder(index: number) {
    setActiveFolder(index);
  }

  return (
    <div className='flex  min-h-screen font-sans'>
      <main className='min-h-screen min-w-full max-w-3xl flex-col items-center justify-between py-16 px-4 sm:items-start text-foreground'>
        <div className='w-fit self-center justify-self-center'>
          <h1 className='text-6xl justify-self-center'>MediKeep</h1>
          <span className='text-sm md:text-2xl'>
            Keep track of your medication
          </span>
        </div>
        <div className='py-8 flex flex-col gap-2 justify-center self-center justify-self-center w-fit'>
          <div className='flex gap-2 justify-center text-sm'>
            <button
              onClick={() => openAddFolder()}
              className='px-2.5 py-1 rounded-full text-xl'
            >
              <FontAwesomeIcon icon={faFolderPlus} />
              Create New Folder
            </button>
          </div>
        </div>
        {folders.length !== 0 && (
          <div className='rounded-2xl w-full justify-self-center md:w-2xl'>
            <div className='flex'>
              {folders[0] &&
                folders.map((folder, index) => {
                  return (
                    <button
                      key={folder.id}
                      onClick={() => changeFolder(index)}
                      className={`px-2.5 py-1 rounded-r-md rounded-l-md rounded-b-none scale-100! active:scale-100! ${
                        index == activeFolder
                          ? 'text-black bg-white font-bold border-2 border-blue-50'
                          : 'bg-[#922b21] text-white opacity-50'
                      }`}
                    >
                      {index == activeFolder ? (
                        <FontAwesomeIcon icon={faFolderOpen} />
                      ) : (
                        <FontAwesomeIcon icon={faFolderClosed} />
                      )}

                      {folder.name}
                    </button>
                  );
                })}
            </div>
            <div className='bg-foreground rounded-2xl rounded-tl-none w-full justify-self-center md:w-2xl'>
              <div className='p-2.5 flex justify-between text-background'>
                <button
                  className=' font-bold '
                  onClick={() => openEditFolder()}
                >
                  <FontAwesomeIcon icon={faPenToSquare} />
                  Rename Folder
                </button>
                <button
                  className=' font-bold '
                  onClick={() => openDeleteFolder()}
                >
                  <FontAwesomeIcon icon={faTrashAlt} />
                  Delete Folder
                </button>
              </div>
              <button
                className='px-2.5 py-5 rounded-full font-bold text-background'
                onClick={() => openAddMed()}
              >
                <FontAwesomeIcon icon={faPills} /> Add New Med
              </button>
              <Meds
                meds={folders[activeFolder].items}
                editMed={handleEditMed}
                deleteMed={handleDeleteMed}
                modalData={modalData}
                setModalData={setModalData}
              />
            </div>
          </div>
        )}

        {modalData.isOpen && <Modal {...modalData} closeModal={closeModal} />}
      </main>
    </div>
  );
}
