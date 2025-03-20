#include <emscripten.h>

extern "C" {
    void drawCircle(int x, int y, int radius, const char* color) {
        EM_ASM_({
            var canvas = document.getElementById('canvas');
            if (!canvas) {
                canvas = document.createElement('canvas');
                canvas.id = 'canvas';
                document.body.appendChild(canvas);

                function resizeCanvas() {
                    canvas.width = window.innerWidth;
                    canvas.height = window.innerHeight;
                    }
                    
                window.addEventListener('resize', resizeCanvas);
                resizeCanvas();
            }

            var ctx = canvas.getContext('2d');
            ctx.fillStyle = UTF8ToString($3);
            ctx.beginPath();
            ctx.arc($0, $1, $2, 0, Math.PI * 2);
            ctx.fill();
        }, x, y, radius, color);
    }

    void clearCanvas() {
        EM_ASM({
            var canvas = document.getElementById('canvas');
            if (canvas) {
                var ctx = canvas.getContext('2d');
                ctx.clearRect(0, 0, canvas.width, canvas.height);  // Clear the canvas
            }
        });
    }

    void drawOnce(void* x){
        drawCircle(50, 50, 50, "red");
        drawCircle(150, 50, 50, "blue");
    }
}

int main() {
    EM_ASM({
        var clearButton = document.createElement('button');
        clearButton.textContent = "Clear Canvas";

        var addButton = document.createElement('button');
        addButton.textContent = "Add Circles";

        document.body.appendChild(clearButton);
        document.body.appendChild(addButton);

        clearButton.addEventListener('click', function() {
            Module._clearCanvas();
        });

        addButton.addEventListener('click', function() {
            Module._drawOnce();
        });

        setTimeout(function() {
            Module._drawOnce();
        }, 500);
    });
    return 0;
}