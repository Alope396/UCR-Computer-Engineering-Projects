// import React, { useState } from 'react';
import './App.css';
import './components/Post/Post.css';
import './components/Reply/Reply.css';
import Post from './components/Post/Post';

function App() {

  return (
    <div className="App">
      <h1>Riv'It</h1>
      <h2>Share all things UCR</h2>
      <Post />
    </div>
  );
}

export default App;
