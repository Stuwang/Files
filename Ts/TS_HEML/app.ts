class Program {

    static tableInited_: Boolean = false;

    public static Run() {
        let table_sub = document.getElementById("table1_sub") as HTMLInputElement;
        // table_sub.onclick = (e) => {
        // 	if (!Program.tableInited_) {
        Program.AddTable();
        // 	Program.tableInited_ = true;
        // }
        // };
        table_sub.click();
        Program.TestTextArea();
        Program.testLiveData();
    }

    public static TestTextArea() {
        let text = document.getElementById("log_area") as HTMLTextAreaElement;
        for (var i = 0; i < 100; ++i) {
            text.value += new Date().toString() + "asdaaaaaaaaaaaaaaaaaaaaa " + i.toString() + " \n";
        }
    }

    public static AddTable() {
        let table = document.getElementById("table1") as HTMLTableElement;
        {
            let tr = document.createElement("tr") as HTMLTableRowElement;
            let head_arr = ["ID", "Name", "Age"];
            head_arr.forEach((value) => {
                let th = document.createElement("th") as HTMLTableHeaderCellElement;
                th.innerHTML = value;
                tr.appendChild(th);
            });
            table.appendChild(tr);
        }
        for (var i = 0; i < 10; i++) {
            let tr = document.createElement("tr") as HTMLTableRowElement;
            let th1 = document.createElement("td") as HTMLTableDataCellElement;
            th1.innerHTML = "id " + i.toString();
            let th2 = document.createElement("td") as HTMLTableDataCellElement;
            th2.innerHTML = "name  " + i.toString();
            let th3 = document.createElement("td") as HTMLTableDataCellElement;
            th3.innerHTML = "age " + i.toString();

            tr.appendChild(th1);
            tr.appendChild(th2);
            tr.appendChild(th3);

            table.appendChild(tr);
        }
    }

    public static testLiveData() {
        {
            let live = new LiveData<string>("");
            live.SetDelegate((oldValue, newValue) => {
                console.log("set old " + oldValue + " to " + newValue);
            });
            live.data = "123456897";
            live.data = "abcdefghijklmnopqrstuvwxyz";
        }
        {
            let live = new LiveData({
                id: 1,
                name: "wangyuan"
            });
            live.SetDelegate((o, n) => {
                console.log("set " +
                    JSON.stringify(o) + " to " +
                    JSON.stringify(n));
            });
            live.data = {
                id: 13,
                name: "hahahhah"
            };
        }

    }

}

interface GetInvokeType<T> {
    (value: T): void;
}

interface SetInvokeType<T> {
    (oldValue: T, newValue: T): void;
}


class LiveData<T>{
    private get_arr_ = new Array<GetInvokeType<T>>();
    private set_arr_ = new Array<SetInvokeType<T>>();
    private _data: T;

    constructor(data: T) {
        this._data = data;
    }

    public GetDelegate(f: GetInvokeType<T>) {
        this.get_arr_.push(f);
    }

    public SetDelegate(f: SetInvokeType<T>) {
        this.set_arr_.push(f);
    }

    public set data(value: T) {
        let old = this._data;
        this.set_arr_.forEach((f) => {
            f(old, value);
        })
        this._data = value;
    }

    public get data(): T {
        let old = this._data;
        this.get_arr_.forEach((e) => {
            e(old);
        })
        return this._data;
    }
}


window.onload = () => {
    Program.Run();
}
