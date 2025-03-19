"use strict";

const DEFAULT = {
  color: "Black",
  background: "White",
  colors: [
    "Black",
    "White",
    "Red",
    "Green",
    "Blue",
    "Yellow",
    "Orange",
    "Purple",
    "Pink",
    "Brown",
    "Gray",
  ],
  name: "variableName",
  messages: {
    copied: "Copied to clipboard!",
    errCopy: "Failed to copy!",
    noText: "Please enter the text!",
  }
}

let currentColor = DEFAULT.color;
let mouseDown = false;

const gridElement = document.getElementById("grid");
const nameInput = document.getElementById("name");
const textAreaElement = document.getElementById("arrayText");
const rootCSS = document.querySelector(':root');

// create list of colors and change current color
function initColors() {
  const currentColorElement = document.getElementById("currentColor");
  currentColorElement.style.backgroundColor = currentColor;
  const ulElement = document.getElementById("colorsList");
  DEFAULT.colors.forEach(color => {
    const liElement = document.createElement("li");
    const spanElement = document.createElement("span");
    const bElement = document.createElement("b");
    spanElement.style.backgroundColor = color;
    bElement.innerHTML = color;
    liElement.id = color;
    liElement.appendChild(spanElement);
    liElement.appendChild(bElement);
    liElement.addEventListener("click", (event) => {
      let id = event.target.id;
      if (!id) {
        id = event.target.parentElement.id
      }
      currentColor = id;
      currentColorElement.style.backgroundColor = currentColor;
    });
    ulElement.appendChild(liElement);
  });
}

// change color of the cell
function changeColor(id) {
  document.getElementById(id).style.backgroundColor = currentColor;
}

// check if mouse pressed
function initMouse() {
  gridElement.onmousedown = () => mouseDown = true;
  document.onmouseup = () => mouseDown = false;
}

// generate grid 16x16
function initGrid() {
  for (let i = 0; i < 16; i++) { // 16 rows
    const rowElement = document.createElement("div");
    rowElement.classList.add("row-item");
    for (let j = 0; j < 16; j++) { // 16 columns
      const colElement = document.createElement("div");
      colElement.id = `${i}-${j}`;
      colElement.classList.add("col-item");
      colElement.style.backgroundColor = DEFAULT.background;
      colElement.addEventListener("mousemove", function (event) {
        if (mouseDown) {
          changeColor(event.target.id);
        }
      });
      colElement.addEventListener("mousedown", function (event) {
        changeColor(event.target.id);
      });
      rowElement.appendChild(colElement);
    }
    gridElement.appendChild(rowElement);
  }
}

// copy text to clipboard
function pasteText(text) {
  navigator.clipboard.writeText(text).then(() => {
    alert(DEFAULT.messages.copied);
  }).catch(err => {
    console.error(DEFAULT.messages.errCopy, err);
  });
}

// save button
function initSave() {
  const saveButton = document.getElementById("save");
  saveButton.addEventListener("click", () => {
    let array2d = getArray2d();
    let text = arrayToC(array2d);
    pasteText(text);
  });
}

// get 2d array from grid
function getArray2d(serpentine = true) {
  let array2d = [];
  const rowItems = document.querySelectorAll(".row-item");
  rowItems.forEach((rowItem, index) => {
    const colItem = rowItem.querySelectorAll(".col-item");
    let rowArray = [];
    colItem.forEach(col => {
      let colorBg = col.style.backgroundColor
      rowArray.push(colorBg.toUpperCase());
    });
    if (index % 2 == 0 && serpentine) {
      rowArray = rowArray.reverse();
    }
    array2d.push(rowArray);
  });
  return array2d;
}

// set 2d array to grid
function setArray2d(array2d) {
  const rowItems = document.querySelectorAll(".row-item");
  rowItems.forEach((rowItem, i) => {
    const colItems = rowItem.querySelectorAll(".col-item");
    colItems.forEach((colItem, j) => {
      colItem.style.backgroundColor = array2d[i][j]
    });
  });
}

// convert 2d array to C array
function arrayToC(array2d) {
  let name = nameInput.value.trim();
  if (name == "") {
    name = DEFAULT.name;
  }
  let strText = "const CRGB " + name + "[16][16] = ";
  strText += "{\n";
  for (let i = 0; i < array2d.length; i++) {
    strText += "{ ";
    for (let j = 0; j < array2d[i].length; j++) {
      strText += array2d[i][j] + ", ";
      if (j == array2d[i].length - 1) {
        strText = strText.slice(0, -2);
      }
    }
    strText += "},\n";
    if (i == array2d.length - 1) {
      strText = strText.slice(0, -2);
    }
  }
  strText += "\n};"
  return strText
}

// load button
function initLoad() {
  const loadButton = document.getElementById("load");
  loadButton.addEventListener("click", () => {
    let textArea = textAreaElement.value.trim();
    if (textArea != "") {
      let array2d = cToArray(textArea);
      setArray2d(array2d);
    } else {
      alert(DEFAULT.messages.noText);
    }
  });
}

// convert C array to 2d array
function cToArray(text) {
  // delete varaible declaration and first claudators
  if (text.includes("=")) {
    text = text.split("=")[1].trim();
  }
  if (text.charAt(0) == "{") {
    text = text.slice(1).trim();
  }
  if (text.charAt(text.length - 1) == ";") {
    text = text.slice(0, -1).trim();
  }
  if (text.charAt(text.length - 1) == "}") {
    text = text.slice(0, -1).trim();
  }
  let rows = text.split("},").map(row => row.replace("\n", "").replace("{", "").replace("}", "").trim());
  // add cols to array
  let array2d = [];
  rows.forEach((row, index) => {
    let cols = row.split(",").map(col => col.trim());
    if (index % 2 == 0) {
      cols = cols.reverse();
    }
    array2d.push(cols);
  })
  return array2d;
}

//bg button
function initBg() {
  const bgButton = document.getElementById("bg");
  bgButton.addEventListener("click", () => {
    const colItems = document.querySelectorAll(".col-item");
    colItems.forEach(colItem => {
      colItem.style.backgroundColor = currentColor;
    });
  });
}

// rotate button
function initRotate() {
  const rotateButton = document.getElementById("rotate");
  rotateButton.addEventListener("click", () => {
    let array2d = getArray2d(false);
    // rotate 90 degrees
    let rotateArray = array2d[0].map((_, index) => array2d.map(row => row[index]).reverse());
    setArray2d(rotateArray);
  });
}

// getColors button
function initGetColors() {
  const getButton = document.getElementById("getColors");
  getButton.addEventListener("click", () => {
    let colorList = []
    // get the list of colors
    document.getElementById("colorsList").querySelectorAll("li").forEach(color => {
      colorList.push({
        name: color.id,
        rgb: window.getComputedStyle(color.querySelector("span")).backgroundColor.slice(4, -1)
      })
    });
    let colorsString = "// Colors:\n";
    colorList.forEach(({ name, rgb }) => {
      colorsString += `#define ${name.toUpperCase()} CRGB(${rgb})\n`;
    });
    pasteText(colorsString);
  });
}

// cellSize button
function initCellSize() {
  const cellSizeButton = document.getElementById("cellSize");
  cellSizeButton.addEventListener("change", (event) => {
    rootCSS.style.setProperty('--cell-size', event.target.value + "px");
  });
}

// INIT
initColors();
initMouse();
initGrid();

// btns
initSave();
initLoad();
initBg();
initRotate();
initGetColors();
initCellSize();
