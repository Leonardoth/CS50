document.querySelector('#redirect').addEventListener('click', function () {
    let destination = document.querySelector('#destination').value;

    window.location.href = `/${destination}.html`
})
