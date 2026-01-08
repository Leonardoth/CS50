# Medikeep

#### Video Demo: [Video Link](https://youtu.be/H6_LG4Q-R3k)

#### Description: Medikeep is a web app that runs entirely local, to help people manage medication dose times, doses remaining and when to refill.

The technologies used in this project are Javascript, HTML, CSS, Next.js, Tailwind and Typescript.

#### Problem

People who care for elderly individuals sometimes have to manage multiple medications, sometimes even for multiple people. This make very easy to lose track of the medication or even their own.

#### Solution

This project was thought just for that, as I have to take care of two elderly parents, having an app to help me to keep track of their medication or even to remember me when it's time to refill it would be very helpful.

## AI Use

AI was used as a tool to help me understand where my logic was wrong, used to save time and not taken as completely right but used to sent me in the direction of documentation, helping me learn terms and what to search for to learn about it.

Also ChatGPT re-wrote my helpers/time.ts and helped me to understand what was wrong with my version.

## Obstacles

Most of my problems was brought not by logic but by typescript, not knowing exactly how to type something took some of my time but using it saved me a lot of time solving bugs and whatnot.

### Crypto.randomUUID ERROR

To generate random IDs for new folders or meds I wanted to use Crypto.randomUUID which is a built-in function in javascript, but it gave me an error because it is not supported in http (dev enviroment runs in http), only in https. This was clarified by chatGPT and solved installing UUID as a fallback, this package let us generate random UUIDs. Thinking back as I write this, there's no use to keep it as a fallback since we only generating random ids that doesn't need to be secure. I'll probably update it to be the main solution.

### Timezone Shifts

To keep track of last update and automatically update the doses remaining, I needed to deal with dates. This proved to be WAY HARDER than I thought since I did not consider the effect of timezones.

I wrote the logic to save the date as ISOString in the local storage and I also wrote the code to calculate the number of doses, but everytime my code was getting 1 dose less than expected.

That's where chatGPT came in, in seconds it explained to me that the problem wasn't the code but the timezone shift that javascript does AUTOMATICALLY when you use new Date(ISOString), it converts to local time, shifting timezones from UTC that's the ISOString format.

I could get to this answer by my own, but it would take a lot of time and reading through docs and testing, chatGPT explained to me and rewrote the code using this approach:

baseDate -> new Date(ISOString)

buildDate -> function that receives a base date and create another from it, getting the day, month, year and receiving hour/minutes as arguments.

It also fixed the 'addDays' function basically the same way, receiving a base date and creating a new one from it.

Further tests proved that the code was right, the function gave the outputs expected in multiple cases. Maybe it still have edge cases that it can be a problem but for now it's working as expected.

### Typescript

I've done simpler things with typescript so I hadn't run into problems that I did in this project. Creating types is great to avoid common mistakes and always know what your code expect as input and what will be it's output. My biggest problem was creating the type for Modal, where it should have all the information needed to create new folders or new meds, a function to accept parameters that wouldn't always be the same and sometimes they would be identical, e.g., `folder has id and name, med has id, name, pills, takeAt`.

This made me run into some problems with typescript specifically because the modal also has a 'type' that should determine which kind of function and info that modal should have. This logic is inside a switch in the components/Modal.tsx where it had no problem, but as soon as I created react components for each modal (components/Modals) typescript couldn't figure which modal was each. Took me sometime and chatGPT although helpful was not explaining correctly, until it did.

The solution was doing two things:

1. Creating a type for each modal, rewriting the original type that just left optional properties. Creating a base type and from it giving it a type/properties in a union, for each type of modal.

2. Inside each component, specifying the model that we were using by the type, 'extracting' and letting typescript know which it was, getting rid of the problem.

```
# components/Modals/NewMed.tsx

type NewMedProps = Extract<ModalProps, { type: 'New Med' }>;
```

## Files

#### Page.ts

This is our main page and main file, since it's the 'parent' its from where the functions are passed to Modal and child components.

In this component is defined that when the page loads on the client (logic inside a useEffect with [] as dependency), we get the saved object, we also call the update to update the meds based on time passed since last save and after, we update the lastUpdate timestamp.

In this file we also define the modalData object, that defines when the modal is open, it's type and what information it has. This is passed down to modal and to functions that will update it in anyway.

#### ./components/

In this folder is every component that is displayed to the user.

`Meds.tsx` -> Container that displays medications

`Med.tsx` -> Is how a medication is displayed inside the container

`Modal.tsx` -> This is the Modal that is the container where each type of modal is displayed inside.

#### ./components/Modals

Modals to handle 'CRUD' of meds: `NewMed.tsx, EditMed.tsx, DeleteConfirm.tsx`
Modals to handle 'CRUD' of folders: `NewFolder.tsx, EditFolder.tsx, DeleteConfirm.tsx`

`DeleteConfirm` is used for both and it's logic can be implemented to other components like New and Edit.

#### ./lib/

Here we'll find functions that are part of the business logic, that handle folders(folders.ts), meds(med.ts) and localstorage(storage.ts), functions that handle time-related logic (time.ts) and generation of id (id.ts) and index.ts to export it all from just one file.

#### ./types/

Here we also use index.ts to export it all from one file and we have the most important types of our app defined: Modals, MedData and Folder.

## Next Steps

1. Better design is the absolute next step.
2. Adding tests so it's easier to implement new things (and I'll also learn more about tests)
3. Features planned: Notifications (sound, action and timed), Button to search for medication online
