window.onload = function() {
    var ws = null;

    var send_b = document.getElementById(
        "send_button");
    var open_b = document.getElementById(
        "open_button");
    var close_b = document.getElementById(
        "close_button");


    addData = function(data) {
        console.log(data);
    };

    open_b.onclick = function(e) {
        if (ws != null) {
            switch (ws.readyState) {
                case WebSocket.CONNECTING:
                    addData("正在打开连接中...");
                    return;
                case WebSocket.OPEN:
                    addData("连接已经打开");
                    return;
                case WebSocket.CLOSING:
                    addData("连接正在关闭");
                    return;
                    break;
                case WebSocket.CLOSED:
                    break;
                default:
                    break;
            }
        }
        ws = new WebSocket(
            "ws://localhost:8080/echo");
        ws.onopen = function(e) {
            addData("连接成功");
        }
        ws.onclose = function(e) {
            addData("关闭成功");
        }
        ws.onmessage = function(e) {
            addData("recv msg :" + e.data);
        }
    }

    close_b.onclick = function(e) {
        if (ws != null && ws.readyState == WebSocket.OPEN) {
            ws.close();
        }else{
            addData("连接未打开，不能关闭");
        }
    }

    send_b.onclick = function(e) {
        if (ws.readyState != WebSocket.OPEN) {
            addData("抱歉，现在连接没有打开");
        }
        ws.send("hello " + new Date());
    }

};
