// Build times safely WITHOUT timezone conversion -- chatGPT
export function buildLocalDate(base: Date, hhmm: string): Date {
  const [h, m] = hhmm.split(':').map(Number);
  return new Date(
    base.getFullYear(),
    base.getMonth(),
    base.getDate(),
    h,
    m,
    0,
    0
  );
}

// Add days safely WITHOUT timezone bugs -- chatGPT
export function addDaysLocal(base: Date, days: number): Date {
  return new Date(base.getFullYear(), base.getMonth(), base.getDate() + days);
}
