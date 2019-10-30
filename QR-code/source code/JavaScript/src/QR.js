let NUMERICO = 'NUMERICO'
let ALPHANUMERICO = 'ALPHANUMERICO'
let BYTE = 'BYTE'
function print(msg){
    return console.log(msg);
}

class QR{
    constructor(msg){
        this.msg = msg;
    }
    analise(){
         this.modo_codificacao = NUMERICO;
        let c ;
        let especiais = Array.prototype.map.call(' $*+./:', (x)=> {return x.charCodeAt(0);});
        for (let i = 0;i<this.msg.length;i++){
            c = this.msg.charCodeAt(i);

            if(c>= 48 && c <= 57)
                continue;
            if((c>=65 && c<=91) || especiais.includes(c)){
                this.modo_codificacao = ALPHANUMERICO;
                continue;
            }
            this.modo_codificacao = BYTE;
            break;
        }
    }

}
let q = new QR('UAU');
q.analise();
