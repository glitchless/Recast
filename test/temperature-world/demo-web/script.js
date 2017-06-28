/**
 * Created by Oleg Morozenkov on 03.04.17.
 */

var scene, camera, renderer;

var clock = new THREE.Clock();
var keyboard = new KeyboardState();

var meshCache = null;

init();
animate();

function init() {
    scene = new THREE.Scene();

    camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 1, 10000);
    camera.position.x = 100;
    camera.position.y = 300;
    camera.position.z = 1200;
    camera.rotateY(-0.7);

    continuouslyLoadWorldAsync(function (world) {
        initWorld(scene, world);
    }, 1000);

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
        camera.position.z = 2000;
        camera.rotation.x = 0;
        camera.rotation.y = 0;
        camera.rotation.z = 0;
    }

    renderer.render(scene, camera);
    requestAnimationFrame(animate);
}

function continuouslyLoadWorldAsync(callback, delay) {
    loadWorldAsync(function (world) {
        callback(world);
        setTimeout(function () {
            continuouslyLoadWorldAsync(callback, delay);
        }, delay);
    });
}

function loadWorldAsync(callback) {
    var xmlhttp = new XMLHttpRequest();

    xmlhttp.onreadystatechange = function () {
        if (xmlhttp.readyState == XMLHttpRequest.DONE) {
            if (xmlhttp.status == 200) {
                callback(JSON.parse(xmlhttp.responseText)['blocks']);
                document.getElementById('info').innerHTML = '';
            }
        }
    };

    xmlhttp.open("GET", "/get_world", true);
    xmlhttp.send();
}

function initWorld(scene, world) {
    if (meshCache == null) {
        meshCache = new Map();
        world.forEach(function (block) {
            var geometry = new THREE.BoxGeometry(5, 5, 5);
            var material = new THREE.MeshBasicMaterial({color: new THREE.Color(block.t / 100, 0, 0.25)});

            var mesh = new THREE.Mesh(geometry, material);
            mesh.position.x = block.x * 100;
            mesh.position.y = block.y * 100;
            mesh.position.z = block.z * 100;
            scene.add(mesh);
            meshCache.set(block.x + ' ' + block.y + ' ' + block.z, mesh);
        });
    } else {
        world.forEach(function (block) {
            var mesh = meshCache.get(block.x + ' ' + block.y + ' ' + block.z);
            if (mesh == null) {
                console.error('mesh == null');
                return;
            }
            mesh.material.color.r = block.t / 100;
        });
    }
}

function clearScene(scene) {
    scene.remove.apply(scene, scene.children);
}