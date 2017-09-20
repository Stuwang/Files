class Program {

    ws: WebSocket = null;

    public addData(data:string){
        // console.log(data);
        let text = document.getElementById("text");
        
        let newText = document.createElement("div");
        newText.innerText = data;

        text.appendChild(newText);
    }

    public Run() {
        let send_b = document.getElementById("send_button") as HTMLInputElement;
        let open_b = document.getElementById("open_button") as HTMLInputElement;
        let close_b = document.getElementById("close_button") as HTMLInputElement;
        open_b.onclick = (e) =>{
            let ws = this.ws;
            let addData = this.addData;
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
                    case WebSocket.CLOSED:
                        break;
                    default:
                        break;
                }
            }
            this.ws = new WebSocket("ws://localhost:8080/echo");
            ws = this.ws;
            ws.onopen = (e)=> {
                addData("连接成功");
            }
            ws.onclose = function(e) {
                addData("关闭成功");
            }
            ws.onmessage = function(e) {
                addData("收到相应:" + e.data);
            }
        }

        close_b.onclick = (e)=> {
            let ws = this.ws;
            let addData = this.addData;

            if (ws != null && ws.readyState == WebSocket.OPEN) {
                ws.close();
            } else {
                addData("连接未打开，不能关闭");
            }
        }

        send_b.onclick = (e)=> {
            let ws = this.ws;
            let addData = this.addData;
            if ( ws == null || ws.readyState != WebSocket.OPEN) {
                addData("抱歉，现在连接没有打开");
                return;
            }
            let msg = "hello " + new Date().toString();
            ws.send(msg);
            addData("发送消息:" + msg);
        }


        this.addData("fot test");
    }
}

let p = new Program();

window.onload = () => {
    p.Run();
}
