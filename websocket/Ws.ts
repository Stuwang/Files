

// class messageEvent{
// 	public data: string;
// }

// interface messageCallback{
// 	(e: messageEvent ):void;
// }

// interface callback{
// 	(e: string): void;
// }

// enum WeState{
// 	CONNECTING = WebSocket.CONNECTING,
// 	OPEN = WebSocket.CLOSED;
// }

// class We {
// 	static CONNECTING: Number;
// 	static OPEN: Number;
// 	static CLOSING: Number;
// 	static CLOSED: Number;

// 	ws: any;

// 	public constructor(url: string){
// 		this.ws = new WebSocket(url);
// 	};
// 	public close():void{
// 		this.ws.close();
// 	};

// 	public set onopen(c:callback){
// 		this.ws.onopen = c;
// 	};
// 	public set onclose(c: callback){
// 		this.ws.onclose = c;
// 	}
// }