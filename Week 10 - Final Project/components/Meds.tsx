import Med from '../components/Med';
import { MedData, ModalProps } from '@/types';

type EditArgs = Pick<MedData, 'id' | 'name' | 'pills' | 'takeAt'>;

interface MedsProps {
  meds: MedData[];
  editMed: (med: EditArgs) => void;
  deleteMed: (id: string) => void;
  modalData: ModalProps;
  setModalData: (value: ModalProps) => void;
}

export default function Meds({
  meds,
  modalData,
  setModalData,
  editMed,
  deleteMed,
}: Readonly<MedsProps>) {
  function handleEdit({ name, id, pills, takeAt }: EditArgs): void {
    setModalData({
      ...modalData,
      isOpen: true,
      type: 'Edit Med',
      id: id,
      name: name,
      pills: pills,
      takeAt: takeAt,
      confirm: (med: EditArgs) => editMed(med),
    });
  }

  function handleDelete(id: string, name: string): void {
    setModalData({
      ...modalData,
      isOpen: true,
      type: 'Delete Med',
      id: id,
      name: name,
      confirm: (id: string) => deleteMed(id),
    });
  }

  return (
    <div className='w-full md:w-2xl flex flex-col gap-5 text-black md:justify-self-center'>
      {meds.length > 0 &&
        meds
          .toSorted((a, b) => a.pills - b.pills)
          .map(({ id, name, pills, date, takeAt }: MedData) => {
            return (
              <Med
                id={id}
                key={id}
                name={name}
                pills={pills}
                takeAt={takeAt}
                date={date}
                edit={() => handleEdit({ id, name, pills, takeAt })}
                remove={() => handleDelete(id, name)}
              />
            );
          })}
    </div>
  );
}
