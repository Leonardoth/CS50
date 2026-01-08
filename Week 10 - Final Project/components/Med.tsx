import { addDaysLocal } from '@/lib/time';
import { MedData } from '../types/MedData';

type MedProps = MedData & {
  edit: () => void;
  remove: () => void;
};

export default function Med({
  name = 'Not Set',
  pills = 0,
  takeAt = [],
  date = new Date().toISOString(),
  edit,
  remove,
}: Readonly<MedProps>) {
  return (
    <div className='p-2.5 relative flex flex-col min-w-full rounded-2xl text-2xl border border-background'>
      <div className='grid grid-cols-2 gap-2 items-center justify-start'>
        <span className='col-span-2'>{name}</span>
        <div className='flex gap-1 col-span-2'>
          <span className='w-fit text-[16px]'>
            Pills left:{' '}
            <span
              className={`px-2 rounded ${
                pills < 10 ? 'bg-primary-red text-white' : 'bg-none'
              }`}
            >
              {pills}
            </span>
          </span>
          <span className='text-sm text-left self-center text-gray-700 font-semibold '>
            {takeAt.length}/day
          </span>
        </div>
      </div>
      <span className='text-sm text-left self-start text-gray-700 font-semibold '>
        Doses:{' '}
        {takeAt
          .toSorted((a, b) => a.localeCompare(b))
          .map((time, index) => {
            if (index == takeAt.length - 1) {
              return <span key={time + index}> {time} </span>;
            }
            return <span key={time + index}> {time} |</span>;
          })}
      </span>
      <span className='mt-2.5 border-t border-gray-400 text-sm'>
        Started: {new Date(date).toLocaleDateString()}
      </span>
      <span className='mt-2.5 border-t border-gray-400 text-sm'>
        Refill Before:{' '}
        {new Date(
          addDaysLocal(new Date(), pills / takeAt.length)
        ).toLocaleDateString()}
      </span>
      <div className='mt-2.5 flex gap-5 justify-between'>
        <button onClick={() => edit()}>Edit</button>
        <button onClick={() => remove()}> Delete</button>
      </div>
    </div>
  );
}
