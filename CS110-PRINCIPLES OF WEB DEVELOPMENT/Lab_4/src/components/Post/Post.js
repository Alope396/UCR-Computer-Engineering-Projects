import React, { useState } from 'react';
import ReactDOM from 'react-dom';
import Reply from '../Reply/Reply';
import reply_img from "./reply_img.png"
import arrow from "./arrow.png"
import arrow_inverted from "./arrow_inverted.png"

export default function Post() {
    const [name, setName] = useState('');
    const [body, setBody] = useState('');
  
    const handleSubmit = (event) => {
        event.preventDefault();
        // console.log(name, body);

        var newPost = document.createElement("div");
        newPost.className = "post";

        var newText = document.createElement("a");
        newText.className = "postText";
        newText.appendChild(document.createTextNode(body));

        var newName = document.createElement("a");
        newName.className = "postName";
        newName.appendChild(document.createTextNode(name));

        var reply = document.createElement("img");
        reply.className = "replyButton";
        reply.src = reply_img;
        reply.appendChild(document.createTextNode("Reply"));
        reply.dataset.replies = 0;
        reply.addEventListener("click", function() {
            var newReply = document.createElement("div");
            newReply.className = "newReply";
            reply.dataset.replies = parseInt(reply.dataset.replies) + 1;

            var parent = reply.closest(".post");
            parent.appendChild(newReply);
            ReactDOM.render(React.createElement(Reply, {replyCount: parseInt(reply.dataset.replies)}), newReply);
        });

        var rating = document.createElement("span");
        rating.className = "rating";
        rating.appendChild(document.createTextNode("0"));

        var upvote = document.createElement("img");
        upvote.className = "upvote";
        upvote.src = arrow;
        upvote.appendChild(document.createTextNode("upvote"));
        upvote.addEventListener("click", () => {
            rating.textContent = parseInt(rating.textContent) + 1;
        })

        var downvote = document.createElement("img");
        downvote.className = "downvote";
        downvote.src = arrow_inverted;
        downvote.appendChild(document.createTextNode("downvote"));
        downvote.addEventListener("click", () => {
            rating.textContent = parseInt(rating.textContent) - 1;
        })

        // newPost.append(newName, document.createElement("br"), 
        // newText, document.createElement("br"),
        // upvote, downvote, rating, document.createElement("br"),
        // reply);

        var top = document.createElement("div");
        top.className = "top";

        var ratingWrap = document.createElement("div");
        ratingWrap.className = "ratingWrap";

        top.append(newName, document.createElement("br"),
        newText);
        
        ratingWrap.append(upvote, document.createElement("br"), rating, document.createElement("br"), downvote);
        
        newPost.append(top, ratingWrap, document.createElement("br"), document.createElement("br"), reply);

        document.querySelector(".App").append(newPost);
        setBody('');
        setName('');
        document.getElementById("name").value = "";
        document.getElementById("body").value = "";
        // console.log("cleared");
    };

    var disableButton = (name.length === 0) || (body.length === 0);

    return(
        <div className='outerContainer'>
            <h3>New Post</h3>
            <form className='container' onSubmit={handleSubmit}>
                <div>
                    <input className='name' type="text" id="name" placeholder="Name..." onChange={(e) => setName(e.target.value)}></input>
                </div>
                <div>
                    <input className='text' type="text" id="body" placeholder="Write a new post..." onChange={(e) => setBody(e.target.value)}></input>
                </div>
                <button className='submit' type="submit" disabled={disableButton}>Submit</button>
            </form>
        </div>
    );
}