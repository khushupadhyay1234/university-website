// Optional JavaScript for handling dropdowns on mobile or touchscreens
const dropdown = document.querySelector('#about');

dropdown.addEventListener('click', function() {
    const dropdownContent = this.querySelector('.dropdown-content');
    dropdownContent.style.display = dropdownContent.style.display === 'flex' ? 'none' : 'flex';
});
