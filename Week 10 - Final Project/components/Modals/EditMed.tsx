import { ModalProps } from '@/types';
import { useState } from 'react';

type EditMedProps = Extract<ModalProps, { type: 'Edit Med' }>;

export default function EditMed({
  id,
  name,
  pills,
  takeAt,
  confirm,
  closeModal,
}: Readonly<EditMedProps>) {
  const [newName, setNewName] = useState(name);
  const [newPills, setNewPills] = useState(pills);
  const [selectedTime, setSelectedTime] = useState('');
  const [times, setTimes] = useState(takeAt);

  function submit() {
    confirm({ id, name: newName, pills: newPills, takeAt: times });
  }

  function addTime(newTime: string) {
    if (newTime == '') return;
    if (times.some(time => time == newTime)) return;
    setTimes(prev => [...prev, newTime]);
  }

  function removeTime(index: number) {
    setTimes(prev => prev.filter((_, i) => i !== index));
  }

  return (
    <div className='fixed p-5 flex flex-col top-1/2 left-1/2 -translate-y-1/2 -translate-x-1/2 md:top-0 md:left-0 md:translate-x-1/2 md:translate-y-1/2 z-10 min-w-80 md:min-w-1/2 min-h-1/2 overflow-hidden bg-gray-300 text-black border-3 border-gray-700 rounded-xl'>
      <h1 className='text-black w-full bg-amber-300'>Edit Med</h1>
      <div className='flex flex-col gap-2.5 p-2 '>
        <form action={submit}>
          <div>
            <label htmlFor='name' aria-label='name'>
              Medication:{' '}
            </label>
            <input
              name='name'
              className='w-full'
              placeholder='e.g.: Generic Medication 50mg'
              autoFocus
              autoComplete='off'
              type='text'
              value={newName}
              onInput={e => setNewName(e.currentTarget.value)}
              required
            />
          </div>
          <div>
            <label htmlFor='pills' aria-label='name'>
              Pills:{' '}
            </label>
            <input
              className='w-10'
              name='pills'
              placeholder='e.g.: 30'
              required
              type='number'
              value={Math.max(newPills, 0)}
              onInput={e => {
                setNewPills(Number.parseInt(e.currentTarget.value));
              }}
            />
          </div>
          <div>
            <label htmlFor='time' aria-label='name'>
              Time:{' '}
            </label>
            <input
              className='w-30'
              name='time'
              placeholder='e.g.: X a day'
              required={times.length < 1}
              type='time'
              value={selectedTime}
              onChange={e => {
                setSelectedTime(e.currentTarget.value);
              }}
            />
            <button
              className='mx-2 p-1 text-sm bg-primary-red text-white'
              type='button'
              onClick={() => addTime(selectedTime)}
            >
              Add Time
            </button>

            <div>
              <span>
                <div className='flex gap-1 my-2 text-sm max-w-100 flex-wrap'>
                  {times
                    .toSorted((a, b) => a.localeCompare(b))
                    .map((time, index) => (
                      <span
                        key={time + index}
                        className='flex gap-2 align-center justify-center w-fit border-2 p-1 text-black rounded-2xl'
                      >
                        <span> {time} </span>
                        <button
                          className='font-bold text-xs bg-primary-red text-white w-5 h-5 rounded-full self-center'
                          onClick={() => removeTime(index)}
                        >
                          X
                        </button>
                      </span>
                    ))}
                </div>
                {times.length > 0 && (
                  <div>
                    <span>Doses: </span>
                    <span> {times.length}</span>
                    <span>/day</span>
                  </div>
                )}
              </span>
            </div>
          </div>
          <div className='my-5 flex w-full justify-between'>
            <button
              className='hover:cursor-pointer text-black border-2 border-black bg-white rounded-full p-2 '
              type='button'
              onClick={() => closeModal()}
            >
              Cancel
            </button>
            <button
              className=' hover:cursor-pointer text-black bg-green-600  rounded-full min-w-1/3  disabled:bg-gray-400 disabled:text-gray-700'
              disabled={newName == '' || pills == undefined}
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
