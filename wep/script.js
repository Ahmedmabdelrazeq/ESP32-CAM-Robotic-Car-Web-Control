function sendCommand(cmd) {
  fetch(`/action?go=${cmd}`).catch(err => console.error(err));
}

function fetchDistance() {
  fetch("/get_distance")
    .then(res => res.json())
    .then(data => {
      document.getElementById("distance-info").textContent =
        `${data.distance} cm`;
    })
    .catch(err => console.error(err));
}

document.addEventListener("keydown", e => {
  const key = e.key.toLowerCase();
  const commands = {
    i: "forward",
    m: "backward",
    j: "left",
    l: "right",
    k: "stop",
    f: "flash_on",
    g: "flash_off",
    a: "servo_left",
    s: "servo_right",
    w: "servo_up",
    z: "servo_down"
  };

  if (commands[key]) {
    sendCommand(commands[key]);
  }
});

document.addEventListener("keyup", e => {
  if ("imjl".includes(e.key.toLowerCase())) {
    sendCommand("stop");
  }
});

window.onload = () => {
  document.getElementById("video-stream").src =
    window.location.href.slice(0, -1) + ":81/stream";

  setInterval(fetchDistance, 150);
};
