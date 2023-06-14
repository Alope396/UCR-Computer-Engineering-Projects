import React, { useState } from 'react';
import ReactDOM from 'react-dom';
import reply_img from "./../Post/reply_img.png";
import arrow from "./../Post/arrow.png";
import arrow_inverted from "./../Post/arrow_inverted.png";



export default function Reply(props) {
    const [name, setName] = useState('');
    const [body, setBody] = useState('');
    const [visible, setVisible] = useState(true);
  
    const handleSubmit = (event) => {
        event.preventDefault();
        var newReply = document.createElement("div");
        newReply.className = "reply";

        var newReplyText = document.createElement("a");
        newReplyText.className = "newReplyText";
        newReplyText.appendChild(document.createTextNode(body));

        var newReplyName = document.createElement("a");
        newReplyName.className = "newReplyName";
        newReplyName.appendChild(document.createTextNode(name));

        var reply = document.createElement("img");
        reply.className = "replyButton";
        reply.src = reply_img;
        reply.appendChild(document.createTextNode("Reply"));
        reply.dataset.replies = props.replyCount;
        reply.addEventListener("click", function() {
            console.log("Num replies ", props.replyCount);
            if (props.replyCount < 2) {
                var lastReply = document.createElement("div");
                lastReply.className = "lastReply";
                reply.dataset.replies = parseInt(reply.dataset.replies) + 1;

                //newReply.appendChild(lastReply);
                //ReactDOM.createRoot(document.querySelector(".newReply")).render(<Reply replyCount={parseInt(reply.dataset.replies)}/>);
                var parent = reply.closest(".reply");
                parent.appendChild(lastReply);
                ReactDOM.render(React.createElement(Reply, {replyCount: parseInt(reply.dataset.replies)}), lastReply);
            }
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

        var top = document.createElement("div");
        top.className = "top";

        var ratingWrap = document.createElement("div");
        ratingWrap.className = "ratingWrap";

        top.append(newReplyName, document.createElement("br"),
        newReplyText);
        
        ratingWrap.append(upvote, document.createElement("br"), rating, document.createElement("br"), downvote);
        
        newReply.append(top, ratingWrap, document.createElement("br"), document.createElement("br"), reply);

        // document.querySelectorAll(".post").append(newReply);
        // Want to add this reply to the last made post
        var allPosts = document.querySelectorAll(".post");
        allPosts[allPosts.length - 1].appendChild(newReply);
        setBody('');
        setName('');
        setVisible(!visible);
    };

    var disableButton = (name.length === 0) || (body.length === 0);

    return(
        <div>
            {visible && (
                <form onSubmit={handleSubmit}>
                    <div>
                        <input className='name' type="text" id="name" placeholder="Name..." onChange={(e) => setName(e.target.value)}></input>
                    </div>
                    <div>
                        <input className='text' type="text" id="body" placeholder="Reply..." onChange={(e) => setBody(e.target.value)}></input>
                </div>
                <button className='submit' type="submit" disabled={disableButton}>Submit</button>
                </form>
            )}
        </div>
    );
}