const express = require('express');
const bodyParser = require('body-parser');
const cors = require('cors');

const app = express();
const port = 3000;

let books = [];

app.use(cors());

app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

app.get('/', function (req, res){
    res.sendFile(__dirname+'/book-list.html');
})

app.get('/book-list-js', function (req, res){
    res.sendFile(__dirname+'/book-list.js');
})

app.get('/book-list', function (req, res){
    res.sendFile(__dirname+'/book-list.html');
})

app.get('/new-book', function (req, res){
    res.sendFile(__dirname+'/new-book.html');
})

app.post('/book', (req, res) => {
    // Code here
    const book = req.body;
    // console.log(book);
    books.push(book);
    res.redirect('/book-list');
});

app.get('/books', (req, res) => {
    res.json(books);
});

app.get('/book/:isbn', (req, res) => {
    const isbn = req.params.isbn;
    const newBook = req.body;

    for (let i = 0; i < books.length; i++) {
        let book = books[i];

        if(book.isbn === isbn) {
            return(res.json(book));
        }
    }

    res.send("Unable to find book with ISBN: " + isbn);
});

app.post('/updateBook/:isbn', (req, res) => {
    const isbn = req.params.isbn;
    const newBook = req.body;

    for (let i = 0; i < books.length; i++) {
        let book = books[i];
        if(book.isbn === isbn) {
            books[i] = newBook;
            // res.send("Book has been updated");
        }
    }
    // res.send("Failed to update book");
    res.redirect('/book-list');
});

app.post('/deleteBook/:isbn', (req, res) => {
    const isbn = req.params.isbn;
    
    for (let i = 0; i < books.length; i++) {
        let book = books[i];
        if(book.isbn === isbn) {
            books.splice(i, 1);
            // res.send("Book has been deleted");
        }
    }
    // res.send("Failed to delete book");
    res.redirect('/book-list');
});

app.listen(port, () => console.log(`Book API listening on port ${port}!`));