/**
 * Created by Oleg Morozenkov on 03.04.17.
 */

var scene, camera, renderer;

var clock = new THREE.Clock();
var keyboard = new KeyboardState();

init();
animate();

function init() {
    scene = new THREE.Scene();

    camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 1, 10000);
    camera.position.z = 1000;

    continuouslyLoadWorldAsync(function (world) {
        initWorld(scene, world);
    }, 10000);

    renderer = new THREE.WebGLRenderer();
    renderer.setSize(window.innerWidth, window.innerHeight);

    document.body.appendChild(renderer.domElement);
}

function animate() {
    var dt = clock.getDelta();
    keyboard.update();

    if (keyboard.pressed("W")) {
        camera.translateZ(-500 * dt);
    }
    if (keyboard.pressed("S")) {
        camera.translateZ(500 * dt);
    }
    if (keyboard.pressed("A")) {
        camera.rotateY(1 * dt);
    }
    if (keyboard.pressed("D")) {
        camera.rotateY(-1 * dt);
    }
    if (keyboard.pressed("up")) {
        camera.translateY(500 * dt);
    }
    if (keyboard.pressed("down")) {
        camera.translateY(-500 * dt);
    }
    if (keyboard.pressed("left")) {
        camera.translateX(-500 * dt);
    }
    if (keyboard.pressed("right")) {
        camera.translateX(500 * dt);
    }
    if (keyboard.pressed("Z")) {
        camera.position.x = 0;
        camera.position.y = 0;
        camera.position.z = 1000;
        camera.rotation.x = 0;
        camera.rotation.y = 0;
        camera.rotation.z = 0;
    }

    renderer.render(scene, camera);
    requestAnimationFrame(animate);
}

function continuouslyLoadWorldAsync(callback, delay) {
    loadWorldAsync(callback);
    // updateWorld(); // TODO
    setTimeout(function () {
        continuouslyLoadWorldAsync(callback, delay);
    }, delay);
}

function loadWorldAsync(callback) {
    var xmlhttp = new XMLHttpRequest();

    xmlhttp.onreadystatechange = function () {
        if (xmlhttp.readyState == XMLHttpRequest.DONE) {
            if (xmlhttp.status == 200) {
                callback(JSON.parse(xmlhttp.responseText)['blocks']);
            }
        }
    };

    xmlhttp.open("GET", "/get_world", true);
    xmlhttp.send();
}

function initWorld(scene, world) {
    clearScene(scene);
    world.forEach(function (block) {
        var geometry = new THREE.BoxGeometry(5, 5, 5);
        var material = new THREE.MeshBasicMaterial({color: new THREE.Color(block.t / 100, 0.2, 0), });

        var mesh = new THREE.Mesh(geometry, material);
        mesh.position.x = block.x * 100;
        mesh.position.y = block.y * 100;
        mesh.position.z = block.z * 100;
        scene.add(mesh);
    });
}

function updateWorld() {
    var xmlhttp = new XMLHttpRequest();

    xmlhttp.onreadystatechange = function () {
        if (xmlhttp.readyState == XMLHttpRequest.DONE) {
            console.log('update world: response ' + xmlhttp.status);
        }
    };

    xmlhttp.open("GET", "/update_world", true);
    xmlhttp.send();
}

function clearScene(scene) {
    scene.remove.apply(scene, scene.children);
}