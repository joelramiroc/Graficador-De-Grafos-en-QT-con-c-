#include "dragwidget.h"

DragWidget::DragWidget(QWidget *parent)
    : QFrame(parent)
{    
    this->grafoActual="Normal";
    this->listaCirculosGrafo = new Lista<circuloVertice*>();
    this->grafoPrincipal = new Grafo();
    this->imprimir = grafoPrincipal;
    setMinimumSize(1280,720);
    setFrameStyle(QFrame::Raised | QFrame::WinPanel);
    setAcceptDrops(true);
    mostrarInfo = new infoMostrar(this);
    this->nombreVertice = new QTextEdit(this);
    this->nombreInicio = new QTextEdit(this);
    this->nombreFin = new QTextEdit(this);
    this->peso = new QTextEdit(this);
    nombreVertice->setGeometry(10,03,200,22);
    nombreVertice->setPlaceholderText("Nombre");
    nombreInicio->setGeometry(500,03,200,22);
    nombreInicio->setPlaceholderText("Vertice Inicial");
    nombreFin->setGeometry(710,03,200,22);
    nombreFin->setPlaceholderText("Vertice Final");
    peso->setGeometry(920,03,200,22);
    peso->setPlaceholderText("Peso Arista");
}

void DragWidget::handleSubmit()
{
    if(this->imprimir!=this->grafoPrincipal)
    {
        mensaje.setText("Tiene que estar en el grafo principal para habilitar essta funcion");
        mensaje.show();
        return;
    }else if(this->grafoPrincipal->listaVertices->getSize()<2)
    {
        mensaje.setText("Tiene que haber al menos dos vertices para poder crear una arista");
        mensaje.show();
        return;
    }

    string inicio = (this->nombreInicio->toPlainText()).toStdString();
    string fin = (this->nombreFin->toPlainText()).toStdString();
    string nombrep = (this->peso->toPlainText()).toStdString();

    if(inicio=="" && fin=="" && nombrep=="")
    {
        mensaje.setText("Igrese un vertice inicial, final y un peso para poder crear la arista");
        mensaje.show();
        return;
    }else if(inicio=="" && fin=="" && nombrep!="")
    {
        mensaje.setText("Ingrese un vertice inicial y final para crear la arista");
        mensaje.show();
        return;
    }else if(inicio!="" && fin!="" && nombrep=="")
    {
        mensaje.setText("Ingrese un peso para  crear la arista");
        mensaje.show();
        return;
    }else if(inicio=="" && nombrep=="")
    {
        mensaje.setText("Ingrese un vertice inicial y un peso para crear la arista");
        mensaje.show();
        return;
    }else if(fin=="" && nombrep=="")
    {
        mensaje.setText("Ingrese un vertice final y un peso para crear la arista");
        mensaje.show();
        return;
    }else if(inicio=="")
    {
        mensaje.setText("Ingrese un vertice inicial para crear la arista");
        mensaje.show();
        return;
    }else if(fin=="")
    {
        mensaje.setText("Ingrese un vertice final para crear la arista");
        mensaje.show();
        return;
    }
    int n=0;
    try{
        n=atoi(nombrep.c_str());
    }catch(exception e)
    {
        return;
    }
    Vertice* primero = this->grafoPrincipal->getvertice(inicio);
    Vertice* segundo = this->grafoPrincipal->getvertice(fin);
    if(primero==nullptr && segundo==nullptr)
    {
        mensaje.setText("Necesita ingresar nombre correcto de vertice inicial y final");
        mensaje.show();
        return;
    }else if(primero==nullptr)
    {
        mensaje.setText("Necesita ingresar nombre correcto de vertice inicial");
        mensaje.show();
        return;
    }else if(segundo==nullptr)
    {
        mensaje.setText("Necesita ingresar nombre correcto de vertice final");
        mensaje.show();
        return;
    }

    bool res = this->grafoPrincipal->insertarArista(primero,segundo,n);
    if(!res)
    {
        mensaje.setText("Ya existe una Arista para esa conexion.");
        mensaje.show();
        return;
    }
    this->update();
    this->setText();
}

void DragWidget::handleSubmitDelet()
{
    if(this->imprimir!=this->grafoPrincipal)
    {
        mensaje.setText("Tiene que estar en el grafo principal para habilitar esta funcion");
        mensaje.show();
        return;
    }else if(this->grafoPrincipal->listaVertices->getSize()<2)
    {
        mensaje.setText("Tiene que haber al menos dos vertices para poder eliminar una arista");
        mensaje.show();
        return;
    }
    string nombrep = (this->nombreInicio->toPlainText()).toStdString();
    string nombre = (this->nombreFin->toPlainText()).toStdString();

    if(nombrep=="" && nombre=="")
    {
        mensaje.setText("Ingrese una arista inicial y final");
        mensaje.show();
        return;
    }else if(nombrep=="")
    {
        mensaje.setText("Ingrese una arista inicial");
        mensaje.show();
        return;
    }else if(nombre=="")
    {
        mensaje.setText("Ingrese una arista final");
        mensaje.show();
        return;
    }
    bool primero = this->grafoPrincipal->existeVertice(nombrep);
    bool segundo = this->grafoPrincipal->existeVertice(nombre);
    if(!primero && !segundo)
    {
        mensaje.setText("No se encontro un vertice inicial y final con ese nombre");
        mensaje.show();
        return;
    }else if(!primero)
    {
        mensaje.setText("No se encontro un vertice inicial con ese nombre");
        mensaje.show();
        return;
    }else if(!segundo)
    {
        mensaje.setText("No se encontro un vertice final con ese nombre");
        mensaje.show();
        return;
    }
    bool res = this->grafoPrincipal->eliminarArista(nombrep,nombre);
    if(!res)
    {
        mensaje.setText("No se encontro la Arista a eliminar.");
        mensaje.show();
        return;
    }
    update();
    this->setText();
}

void DragWidget::handleSubmitDeletVertie()
{
    if(this->imprimir!=this->grafoPrincipal)
    {
        mensaje.setText("Tiene que estar en el grafo principal para habilitar esta funcion");
        mensaje.show();
        return;
    }
    string nombre = (this->nombreVertice->toPlainText()).toStdString();

    if(nombre=="")
    {
        mensaje.setText("Ingrese un nombre de vertice");
        mensaje.show();
        return;
    }

    Vertice* primero = this->grafoPrincipal->getvertice(nombre);
    if(primero==nullptr)
    {
        mensaje.setText("No se encontro un vertice con ese nombre");
        mensaje.show();
        return;
    }

    bool res = this->grafoPrincipal->eliminarVertice(nombre);
    if(!res)
    {
        mensaje.setText("No se encontro el Vertice a eliminar.");
        mensaje.show();
        return;
    }
    update();
    this->setText();
}

void DragWidget::setText()
{   this->nombreVertice->setText("");
    this->nombreInicio->setText("");
    this->nombreFin->setText("");
    this->peso->setText("");
}

void DragWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->pos().y()<130)
        return;
    if(this->imprimir!=this->grafoPrincipal)
    {
        mensaje.setText("Tiene que estar en el grafo principal para poder crear un vertice");
        mensaje.show();
        return;
    }
    string nombre = (this->nombreVertice->toPlainText()).toStdString();
    if(nombre=="")
    {
        mensaje.setText("Ingrese un nombre para poder crear un vertice");
        mensaje.show();
        return;
    }else if(this->grafoPrincipal->existeVertice(nombre))
    {
        mensaje.setText("Ya existe un vertice con ese nombre");
        mensaje.show();
        return;
    }
    this->grafoPrincipal->insertarVertice(nombre);
    Vertice* nuevo = this->grafoPrincipal->getvertice(nombre);
    if(nuevo==nullptr || nombre=="")
        return;
    QPoint q= event->pos();
    circuloVertice* c= new circuloVertice();
    c->createVertice(nombre,(q.x()-25),(q.y()-25));
    c->representavertice=nuevo;
    nuevo->dibujado=c;
    this->listaCirculosGrafo->guardar(c);
    update();
    this->setText();
}

void DragWidget::mousePressEvent(QMouseEvent *event)
{
    QPoint pos=event->pos();
    if(pos.x()>945 && pos.x()<1005 && pos.y()>35 && pos.y()<55)
    {
        this->handleSubmit();
    }else if(pos.x()>1035 && pos.x()<1095 && pos.y()>35 && pos.y()<55)
    {
        this->handleSubmitDelet();
    }else if(pos.x()>220 && pos.x()<280 && pos.y()>3 && pos.y()<23)
    {
        this->handleSubmitDeletVertie();
    }else if(pos.x()>10 && pos.x()<60 && pos.y()>35 && pos.y()<55)
    {
        this->grafoToPrincipal();
    }else if(pos.x()>90 && pos.x()<150 && pos.y()>35 && pos.y()<55)
    {
        this->grafoToFloyd();
    }else if(pos.x()>170 && pos.x()<230 && pos.y()>35 && pos.y()<55)
    {
        this->grafoToWarshall();
    }else if(pos.x()>250 && pos.x()<310 && pos.y()>35 && pos.y()<55)
    {
        this->grafoToDjikstra();
    }else if(pos.x()>330 && pos.x()<390 && pos.y()>35 && pos.y()<55)
    {
        this->recorridoAnchura();
    }else if(pos.x()>410 && pos.x()<470 && pos.y()>35 && pos.y()<55)
    {
        this->recorridoProfundidad();
    }else if(pos.x()>490 && pos.x()<550 && pos.y()>35 && pos.y()<55)
    {
        this->grafoPrim();
    }else if(pos.x()>570 && pos.x()<630 && pos.y()>35 && pos.y()<55)
    {
        this->grafoKruskal();
    }
}

void DragWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);


    painter.drawText(330,20,"Grafo Actual: " + this->grafoActual);

    painter.drawLine(0,80,1300,80);

    painter.drawRect(570,35,60,20);
    painter.drawText(579,50,"KRUSKAL");

    painter.drawRect(490,35,60,20);
    painter.drawText(508,50,"PRIM");

    painter.drawRect(410,35,60,20);
    painter.drawText(432,50,"DFS");

    painter.drawRect(330,35,60,20);
    painter.drawText(352,50,"BFS");

    painter.drawRect(250,35,60,20);
    painter.drawText(263,50,"Dijkstra");

    painter.drawRect(10,35,60,20);
    painter.drawText(20,50,"Normal");

    painter.drawRect(90,35,60,20);
    painter.drawText(107,50,"Floyd");

    painter.drawRect(170,35,60,20);
    painter.drawText(180,50,"Warshall");

    painter.drawRect(220,3,60,20);
    painter.drawText(232,18,"Eliminar");

    painter.drawRect(945,35,60,20);
    painter.drawText(955,50,"Insertar");

    painter.drawRect(1035,35,60,20);
    painter.drawText(1045,50,"Eliminar");

    int x1,x2,y1,y2,textX,textY;
    painter.setPen(Qt::red);    
    Nodo<Vertice*>* temporal = this->imprimir->listaVertices->getFirst();
    Nodo<Arista*>* aristaTemporal;
    double ang1;
    while(temporal!=nullptr)
    {
        aristaTemporal = temporal->valor->aristas->getFirst();
        while(aristaTemporal!=nullptr)
        {
            painter.setPen(Qt::black);
            x1=temporal->valor->dibujado->x+25;
            y1=temporal->valor->dibujado->y+25;
            x2= aristaTemporal->valor->verticeFinal->dibujado->x+25;
            y2= aristaTemporal->valor->verticeFinal->dibujado->y+25;
            textX=(x1+x2)/2;
            textY=(y1+y2)/2;
            if(x1!=x2 || y1!=y2)
            {
                ang1=qAtan2((y2-y1),(x2-x1));
                QPoint ellipse1,ellipse2;
                ellipse1.setX((x2-25*qCos(ang1)));
                ellipse1.setY((y2-25*qSin(ang1)));
                ellipse2.setX((x1+25*qCos(ang1)));
                ellipse2.setY((y1+25*qSin(ang1)));
                painter.drawLine(x1,y1,x2,y2);
                painter.setPen(Qt::red);
                painter.setBrush(Qt::red);
                painter.drawEllipse(ellipse1,5,5);
                QString name= QString::fromStdString(to_string(aristaTemporal->valor->peso));
                painter.setPen(Qt::black);
                painter.drawText(textX+2,textY-2,name);
            }
            aristaTemporal = aristaTemporal->siguiente;
        }
        temporal = temporal->siguiente;
    }


    temporal=this->imprimir->listaVertices->getFirst();
    while(temporal!=nullptr)
    {
        painter.setPen(Qt::blue);
        painter.setBrush(Qt::gray);
        painter.drawEllipse(temporal->valor->dibujado->x,temporal->valor->dibujado->y,50,50);
        painter.setPen(Qt::black);
        QString name= QString::fromStdString(temporal->valor->dibujado->name);
        painter.drawText(temporal->valor->dibujado->x-12.5,temporal->valor->dibujado->y-12.5,name);

        temporal=temporal->siguiente;
    }

}

void DragWidget::grafoToWarshall()
{
    this->grafoWarshall = new Grafo();
    this->copyGraphto(grafoWarshall);
    Nodo<Vertice*>* pivote=this->grafoWarshall->listaVertices->getFirst(),*desde,*hasta;
    while(pivote!=nullptr)
    {
        desde=this->grafoWarshall->listaVertices->getFirst();
        while(desde!=nullptr)
        {
            hasta=this->grafoWarshall->listaVertices->getFirst();
            while(hasta!=nullptr)
            {
                if(this->grafoWarshall->existeArista(desde->valor,pivote->valor) && this->grafoWarshall->existeArista(pivote->valor,hasta->valor))
                {
                    int peso = this->grafoWarshall->pesoTotal(desde->valor,pivote->valor) + this->grafoWarshall->pesoTotal(pivote->valor,hasta->valor);
                    int pesoActual=this->grafoWarshall->pesoTotal(desde->valor,hasta->valor);
                    if(pesoActual==-1)
                    {
                            this->grafoWarshall->insertarArista(desde->valor,hasta->valor,peso);
                    }
                }
                hasta = hasta->siguiente;
            }
            desde = desde->siguiente;
        }
        pivote = pivote->siguiente;
    }
    this->grafoActual="Warshall";
    update();
}

void DragWidget::grafoToPrincipal()
{
    this->grafoActual="Normal";
    this->imprimir=this->grafoPrincipal;
    this->update();
}

void DragWidget::grafoToFloyd()
{
    this->grafoFloyd = new Grafo();
    this->copyGraphto(grafoFloyd);
    Arista* arista;
    Nodo<Vertice*>* pivote=this->grafoFloyd->listaVertices->getFirst(),*desde,*hasta;

    while(pivote!=nullptr)
    {
        desde=this->grafoFloyd->listaVertices->getFirst();
        while(desde!=nullptr)
        {
            hasta=this->grafoFloyd->listaVertices->getFirst();
            while(hasta!=nullptr)
            {
                if(this->grafoFloyd->existeArista(desde->valor,pivote->valor) && this->grafoFloyd->existeArista(pivote->valor,hasta->valor))
                {
                    arista = this->grafoFloyd->getArista(desde->valor,hasta->valor);
                    int peso = this->grafoFloyd->pesoTotal(desde->valor,pivote->valor) + this->grafoFloyd->pesoTotal(pivote->valor,hasta->valor);
                    int pesoActual=this->grafoFloyd->pesoTotal(desde->valor,hasta->valor);
                    if(arista==nullptr)
                    {
                        this->grafoFloyd->insertarArista(desde->valor,hasta->valor,peso);
                    }else
                    if(peso < pesoActual)
                    {
                        arista = this->grafoFloyd->getArista(desde->valor,hasta->valor);
                        arista->peso=peso;
                    }else if(pesoActual==-1)
                    {
                            this->grafoFloyd->insertarArista(desde->valor,hasta->valor,peso);
                    }
                }
                hasta = hasta->siguiente;
            }
            desde = desde->siguiente;
        }
        pivote = pivote->siguiente;
    }
    this->grafoActual="Floyd";
    update();
}

void DragWidget::grafoToDjikstra()
{
    this->grafoDijkstra = new Grafo();
    string nombrep = (this->nombreVertice->toPlainText()).toStdString();

    if(this->grafoPrincipal->listaVertices->getSize()==0)
    {
        mensaje.setText("Necesita tener por lo menos un vertice para poder ejecutar Dijkstra");
        mensaje.show();
        return;
    }else if(nombrep=="")
    {
        mensaje.setText("Ingrese un vertice inicial para ejecutar Dijkstra");
        mensaje.show();
        return;
    }

    if(!this->grafoPrincipal->existeVertice(nombrep))
    {
        mensaje.setText("Ingrese un nombre de vertice existente para poder ejecutar Dijkstra");
        mensaje.show();
        return;
    }

    arrayD= new ArrayListP<Vertice*>();
    if(this->grafoPrincipal->listaVertices->getSize()==0)
        return;
    bool visitado[this->grafoPrincipal->listaVertices->getSize()];
    int peso[this->grafoPrincipal->listaVertices->getSize()];
    Nodo<Vertice*>* temporal = this->grafoPrincipal->listaVertices->getFirst();
    Vertice*nuevo;

    while(temporal!=nullptr)
    {
        nuevo= new Vertice();
        nuevo->dibujado=temporal->valor->dibujado;
        nuevo->nombre=temporal->valor->nombre;
        arrayD->guardar(nuevo);
        temporal=temporal->siguiente;
    }

    int max = 2147483647;
    for(int i=0;i<this->grafoPrincipal->listaVertices->getSize();i++)
    {
        visitado[i]=false;
        peso[i]=max;
    }

    Vertice* caminoInicio = new Vertice();
    caminoInicio = this->grafoPrincipal->getvertice(nombrep);
    int pos=arrayD->getPos(caminoInicio);
    visitado[pos]=true;
    Nodo<Arista*>* actualizando;
    Vertice*uGrafoPrincipalU;
    Vertice* uU = new Vertice();
    Vertice* buscar2 = new Vertice();
    int posFinal;
    actualizando=caminoInicio->aristas->getFirst();

    while(actualizando!=nullptr)
    {
        uU->nombre=actualizando->valor->verticeFinal->nombre;
        posFinal=this->arrayD->getPos(uU);
        peso[posFinal]=actualizando->valor->peso;
        actualizando=actualizando->siguiente;
    }

    int menor=pos,posicionfinal,pesoNuevo,peso1,peso2;
    Nodo<Arista*>* aristaRelajadora;

    for(int i=0;i<this->grafoPrincipal->listaVertices->getSize();i++)
    {
        for(int j=0;j<this->grafoPrincipal->listaVertices->getSize();j++)
        {
            peso1=peso[j];
            for(int k=0;k<this->grafoPrincipal->listaVertices->getSize();k++)
            {
                peso2=peso[k];
                if(peso1<peso2 && !visitado[j])
                {
                    menor=j;
                }
            }
        }

        uU=arrayD->buscar(menor);
        visitado[menor]=true;

        uGrafoPrincipalU=this->grafoPrincipal->getvertice(uU->nombre);
        aristaRelajadora=uGrafoPrincipalU->aristas->getFirst();

        while(aristaRelajadora!=nullptr)
        {
            buscar2->nombre=aristaRelajadora->valor->verticeFinal->nombre;
            posicionfinal=arrayD->getPos(buscar2);
            pesoNuevo=peso[menor]+aristaRelajadora->valor->peso;
            if(peso[posicionfinal]>pesoNuevo)
            {
                peso[posicionfinal]=pesoNuevo;
            }
            aristaRelajadora= aristaRelajadora->siguiente;
        }
    }

    Vertice* paraCopiar,*finalCopiar,*devuelto;

    for(int i=0; i<this->grafoPrincipal->listaVertices->getSize();i++)
    {
        paraCopiar=arrayD->buscar(i);
        this->grafoDijkstra->insertarVertice(paraCopiar->nombre);
        devuelto=this->grafoDijkstra->getvertice(paraCopiar->nombre);
        devuelto->dibujado=paraCopiar->dibujado;
    }

    paraCopiar=this->grafoDijkstra->getvertice(nombrep);
    for(int i=0; i<this->grafoPrincipal->listaVertices->getSize();i++)
    {
        if(peso[i]!=max)
        {
            finalCopiar=arrayD->buscar(i);
            this->grafoDijkstra->insertarArista(paraCopiar->nombre,finalCopiar->nombre,peso[i]);
        }
    }

    this->grafoActual="Dijkstra";
    this->imprimir=grafoDijkstra;
    update();
}

void DragWidget::recorridoAnchura()
{
    string origenV =(this->nombreVertice->toPlainText()).toStdString();
    if(origenV=="")
    {
        mensaje.setText("Necesita Ingresar un vertice de origen para el recorrido");
        mensaje.show();
        return;
    }
    Vertice* origen = this->grafoPrincipal->getvertice(origenV);
    if(origen==nullptr)
    {
        mensaje.setText("No se encontro un vertice con ese nombre");
        mensaje.show();
        return;
    }

    Cola<Vertice*>* cola = new Cola<Vertice*>();
    ArrayListP<Vertice*>* listadoNuevo = new ArrayListP<Vertice*>();
    bool visitado[this->grafoPrincipal->listaVertices->getSize()];
    int saltos[this->grafoPrincipal->listaVertices->getSize()];
    Nodo<Vertice*>* recorrerr = this->grafoPrincipal->listaVertices->getFirst();
    Vertice*nuevo;

    while(recorrerr!=nullptr)
    {
        nuevo = new Vertice();
        nuevo->nombre=recorrerr->valor->nombre;
        listadoNuevo->guardar(nuevo);
        recorrerr = recorrerr->siguiente;
    }

    for(int i=0;i<this->grafoPrincipal->listaVertices->getSize();i++)
    {
        visitado[i]=false;
        saltos[i]=-1;
    }

    int pos,peso=0,pos2;
    cola->push_back(origen);
    pos=listadoNuevo->getPos(origen);
    saltos[pos]=0;
    visitado[pos]=true;

    recorrerr = this->grafoPrincipal->listaVertices->getFirst();
    Nodo<Arista*>* recorrido;
    Vertice* obteniendo;
    while(!cola->empty())
    {
        obteniendo=cola->pop_front();
        recorrido=obteniendo->aristas->getFirst();
        while(recorrido!=nullptr)
        {
            pos=listadoNuevo->getPos(recorrido->valor->verticeFinal);

            if(!visitado[pos])
            {
                pos2=listadoNuevo->getPos(recorrido->valor->verticeInicial);
                peso=saltos[pos2];
                saltos[pos]=peso+1;
                visitado[pos]=true;
                cola->push_back(recorrido->valor->verticeFinal);
            }
            recorrido=recorrido->siguiente;
        }
    }

    Vertice* imprimir;
    string textos="";
    for(int i = 0;i<this->grafoPrincipal->listaVertices->getSize();i++)
    {
        imprimir=listadoNuevo->buscar(i);
        if(saltos[i]!=-1)
        {
            textos+= "Nombre: " + imprimir->nombre + ". Saltos:" + to_string( saltos[i])+"\n";
        }
    }
    this->mensaje.setText(QString::fromStdString(textos));
    this->mensaje.show();
}

void DragWidget::copyGraphto(Grafo* nuevo)
{
     Nodo<Vertice*>* temporal = this->grafoPrincipal->listaVertices->getFirst();
     Nodo<Arista*>* temporalA;
     Vertice* circ;
     while(temporal!=nullptr)
     {
         nuevo->insertarVertice(temporal->valor->nombre);
         circ=nuevo->getvertice(temporal->valor->nombre);
         circ->dibujado=temporal->valor->dibujado;
         temporal=temporal->siguiente;
     }

     temporal = this->grafoPrincipal->listaVertices->getFirst();

     while(temporal!=nullptr)
     {
         temporalA =temporal->valor->aristas->getFirst();
         while(temporalA!=nullptr)
         {
             nuevo->insertarArista(temporalA->valor->verticeInicial->nombre,temporalA->valor->verticeFinal->nombre,temporalA->valor->peso);
             temporalA = temporalA->siguiente;
         }
         temporal=temporal->siguiente;
     }
     imprimir=nuevo;
}

void DragWidget::recorridoProfundidad()
{
    string origenV =(this->nombreVertice->toPlainText()).toStdString();
    if(origenV=="")
    {
        mensaje.setText("Necesita Ingresar un vertice de origen para el recorrido");
        mensaje.show();
        return;
    }
    Vertice* origen = this->grafoPrincipal->getvertice(origenV);
    if(origen==nullptr)
    {
        mensaje.setText("No se encontro un vertice con ese nombre");
        mensaje.show();
        return;
    }

    Pila<Vertice*>* pila = new Pila<Vertice*>();
    ArrayListP<Vertice*>* listadoNuevo = new ArrayListP<Vertice*>();
    bool visitado[this->grafoPrincipal->listaVertices->getSize()];
    int padre[this->grafoPrincipal->listaVertices->getSize()];
    Nodo<Vertice*>* recorrerr = this->grafoPrincipal->listaVertices->getFirst();
    Vertice*nuevo;
    while(recorrerr!=nullptr)
    {
        nuevo = new Vertice();
        nuevo->nombre=recorrerr->valor->nombre;
        listadoNuevo->guardar(nuevo);
        recorrerr = recorrerr->siguiente;
    }

    for(int i=0;i<this->grafoPrincipal->listaVertices->getSize();i++)
    {
        visitado[i]=false;
        padre[i]=-1;
    }

    int pos,pos2;
    pila->push_back(origen);
    pos=listadoNuevo->getPos(origen);
    padre[pos]=0;
    visitado[pos]=true;
    recorrerr = this->grafoPrincipal->listaVertices->getFirst();
    Nodo<Arista*>* recorrido;
    Vertice* obteniendo;

    while(!pila->empty())
    {
        obteniendo=pila->pop_back();
        visitado[pos]=true;
        recorrido=obteniendo->aristas->getFirst();
        while(recorrido!=nullptr)
        {
            pos=listadoNuevo->getPos(recorrido->valor->verticeFinal);
            if(!visitado[pos])
            {
                pos2=listadoNuevo->getPos(recorrido->valor->verticeInicial);
                padre[pos]=pos2;
                pila->push_back(recorrido->valor->verticeFinal);
            }
            recorrido=recorrido->siguiente;
        }
    }

    Vertice* imprimir, *padreI;
    string textos="";
    for(int i = 0;i<this->grafoPrincipal->listaVertices->getSize();i++)
    {
        imprimir=listadoNuevo->buscar(i);
        if(padre[i]!=-1)
        {
            padreI=listadoNuevo->buscar(padre[i]);
            textos+= "Nombre:" + imprimir->nombre + ". Padre: " + padreI->nombre +"\n";
        }
    }
    this->mensaje.setText(QString::fromStdString(textos));
    this->mensaje.show();
}

void DragWidget::grafoPrim()
{
    if(this->grafoPrincipal->listaVertices->getSize()==0)
    {
        mensaje.setText("El Grafo esta vacio");
        mensaje.show();
        return;
    }
    Nodo<Vertice*>* Verticerecorrer = this->grafoPrincipal->listaVertices->getFirst();
    string origenV =(Verticerecorrer->valor->nombre);
    Vertice* origen = this->grafoPrincipal->getvertice(origenV);
    this->prim = new Grafo();
    Grafo* grafoNuevo = new Grafo();
    Vertice* temporal, *temporal2;
    while(Verticerecorrer!=nullptr)
    {
        temporal = new Vertice();
        temporal2 = new Vertice();
        temporal->nombre=Verticerecorrer->valor->nombre;
        temporal->dibujado=Verticerecorrer->valor->dibujado;
        temporal2->nombre=Verticerecorrer->valor->nombre;
        temporal2->dibujado=Verticerecorrer->valor->dibujado;
        prim->listaVertices->guardar(temporal);
        grafoNuevo->listaVertices->guardar(temporal2);
        Verticerecorrer = Verticerecorrer->siguiente;
    }

    Verticerecorrer = this->grafoPrincipal->listaVertices->getFirst();
    Nodo<Arista*>* Aristarecorrer;
    bool marcado[this->grafoPrincipal->listaVertices->getSize()];
    int posD=0;
    while(Verticerecorrer!=nullptr)
    {
        marcado[posD]=false;
        posD++;
        Aristarecorrer=Verticerecorrer->valor->aristas->getFirst();
        while(Aristarecorrer!=nullptr)
        {
            prim->insertarArista(Aristarecorrer->valor->verticeInicial->nombre,Aristarecorrer->valor->verticeFinal->nombre,Aristarecorrer->valor->peso);
            prim->insertarArista(Aristarecorrer->valor->verticeFinal->nombre,Aristarecorrer->valor->verticeInicial->nombre,Aristarecorrer->valor->peso);
            Aristarecorrer = Aristarecorrer->siguiente;
        }
        Verticerecorrer = Verticerecorrer->siguiente;
    }

    ArrayListP<InformationPrim*>* aristasComparar = new ArrayListP<InformationPrim*>();
    ArrayListP<InformationPrim*>* aristasFinales = new ArrayListP<InformationPrim*>();
    InformationPrim* guardar;

    Verticerecorrer=prim->listaVertices->buscar(origen);
    Aristarecorrer = Verticerecorrer->valor->aristas->getFirst();

    while(Aristarecorrer!=nullptr)
    {
        guardar = new InformationPrim(Aristarecorrer->valor->verticeInicial->nombre,Aristarecorrer->valor->verticeFinal->nombre,Aristarecorrer->valor->peso);
        aristasComparar->guardar(guardar);
        Aristarecorrer = Aristarecorrer->siguiente;
    }
    posD=0;

    Nodo<InformationPrim*>*electo,*val;
    int mar,pos;
    mar=prim->listaVertices->getPos(origen);
    marcado[mar]=true;
    bool continuar=true;

    while(continuar)
    {

        continuar=false;
        electo=nullptr;
        pos=mar;
        for(int i=0;i<aristasComparar->getSize();i++)
        {
            val=aristasComparar->obtener(i);
            origen=prim->getvertice(val->valor->nombreFin);
            pos=prim->listaVertices->getPos(origen);
            if(!marcado[pos])
            {
                if(electo==nullptr)
                {
                    electo=val;
                }else if(val->valor->peso<electo->valor->peso){
                    electo=val;
                }
                continuar=true;
            }
        }

        if(continuar)
        {
            origen=prim->getvertice(electo->valor->nombreFin);
            pos=prim->listaVertices->getPos(origen);
            marcado[pos]=true;

            Aristarecorrer=origen->aristas->getFirst();
            while(Aristarecorrer !=nullptr)
            {
                guardar = new InformationPrim(Aristarecorrer->valor->verticeInicial->nombre,Aristarecorrer->valor->verticeFinal->nombre,Aristarecorrer->valor->peso);
                aristasComparar->guardar(guardar);
                Aristarecorrer = Aristarecorrer->siguiente;
            }
            guardar = new InformationPrim(electo->valor->nombreInicio,electo->valor->nombreFin,electo->valor->peso);
            aristasFinales->guardar(guardar);
        }
    }



    for(int i=0;i<aristasFinales->getSize();i++)
    {
        guardar=aristasFinales->buscar(i);
        grafoNuevo->insertarArista(guardar->nombreInicio,guardar->nombreFin,guardar->peso);
        grafoNuevo->insertarArista(guardar->nombreFin,guardar->nombreInicio,guardar->peso);
    }

    imprimir=grafoNuevo;
    this->grafoActual="Prim";
    update();
}

void DragWidget::grafoKruskal()
{

    if(this->grafoPrincipal->listaVertices->getSize()==0)
    {
        mensaje.setText("El Grafo esta vacio");
        mensaje.show();
        return;
    }
    Nodo<Vertice*>* Verticerecorrer = this->grafoPrincipal->listaVertices->getFirst();
    string origenV =(Verticerecorrer->valor->nombre);
    Vertice* origen = this->grafoPrincipal->getvertice(origenV);
    this->kruskal = new Grafo();
    Grafo* grafoNuevo = new Grafo();
    Vertice* temporal, *temporal2;
    while(Verticerecorrer!=nullptr)
    {
        temporal = new Vertice();
        temporal2 = new Vertice();
        temporal->nombre=Verticerecorrer->valor->nombre;
        temporal->dibujado=Verticerecorrer->valor->dibujado;
        temporal2->nombre=Verticerecorrer->valor->nombre;
        temporal2->dibujado=Verticerecorrer->valor->dibujado;
        kruskal->listaVertices->guardar(temporal);
        grafoNuevo->listaVertices->guardar(temporal2);
        Verticerecorrer = Verticerecorrer->siguiente;
    }

    Verticerecorrer = this->grafoPrincipal->listaVertices->getFirst();
    Nodo<Arista*>* Aristarecorrer;
    while(Verticerecorrer!=nullptr)
    {
        Aristarecorrer=Verticerecorrer->valor->aristas->getFirst();
        while(Aristarecorrer!=nullptr)
        {
            kruskal->insertarArista(Aristarecorrer->valor->verticeInicial->nombre,Aristarecorrer->valor->verticeFinal->nombre,Aristarecorrer->valor->peso);
            kruskal->insertarArista(Aristarecorrer->valor->verticeFinal->nombre,Aristarecorrer->valor->verticeInicial->nombre,Aristarecorrer->valor->peso);
            Aristarecorrer = Aristarecorrer->siguiente;
        }
        Verticerecorrer = Verticerecorrer->siguiente;
    }

    ArrayListP<InformationPrim*>* aristasComparar = new ArrayListP<InformationPrim*>();
    ArrayListP<InformationPrim*>* conjuntoSolucion = new ArrayListP<InformationPrim*>();
    InformationPrim* guardar;

    Verticerecorrer=kruskal->listaVertices->buscar(origen);

    while(Verticerecorrer!=nullptr)
    {
        Aristarecorrer = Verticerecorrer->valor->aristas->getFirst();
        while(Aristarecorrer!=nullptr)
        {
            guardar = new InformationPrim(Aristarecorrer->valor->verticeInicial->nombre,Aristarecorrer->valor->verticeFinal->nombre,Aristarecorrer->valor->peso);
            aristasComparar->guardar(guardar);
            Aristarecorrer = Aristarecorrer->siguiente;
        }
        Verticerecorrer=Verticerecorrer->siguiente;
    }

    int grupo[kruskal->listaVertices->getSize()];
    for(int i=0; i<kruskal->listaVertices->getSize();i++)
    {
        grupo[i]=i;
    }

    Nodo<InformationPrim*>*c1,*c2,*sus;

    for(int i=0;i<aristasComparar->getSize();i++)
    {
        for(int j=0;j<aristasComparar->getSize();j++)
        {
            c1=aristasComparar->obtener(i);
            c2=aristasComparar->obtener(j);

            if(c2->valor->peso < c1->valor->peso)
            {
                aristasComparar->change(i,j);
            }
        }
    }
    for(int j=0;j<aristasComparar->getSize();j++)
    {
        c1=aristasComparar->obtener(j);
        cout<<c1->valor->nombreInicio<<endl;
        cout<<c1->valor->peso<<endl;
        cout<<c1->valor->nombreFin<<endl;
        cout<<"==============================================================="<<endl;
    }
    int pos1=0,pos2=0;
    Vertice* obtenido = new Vertice();
    for(int contara=aristasComparar->getSize()-1;contara!=-1;contara--)
    {
        c1=aristasComparar->obtener(contara);
        obtenido->nombre=c1->valor->nombreFin;
        string obs=obtenido->nombre;
        pos1=kruskal->listaVertices->getPos(obtenido);
        obtenido->nombre=c1->valor->nombreInicio;
        string ob=obtenido->nombre;
        pos2=kruskal->listaVertices->getPos(obtenido);
        if(grupo[pos1]!=grupo[pos2])
        {
            guardar = new InformationPrim(c1->valor->nombreInicio,c1->valor->nombreFin,c1->valor->peso);
            conjuntoSolucion->guardar(guardar);
            int comparar=grupo[pos1];
            int sustituir=grupo[pos2];
            for(int i=0;i<kruskal->listaVertices->getSize();i++)
            {
                int grupoI=grupo[i];
                if(grupo[i]==comparar)
                {
                    grupo[i]=sustituir;
                }
            }
        }
    }

    for(int i=0;i<conjuntoSolucion->getSize();i++)
    {
        sus=conjuntoSolucion->obtener(i);
        grafoNuevo->insertarArista(sus->valor->nombreInicio,sus->valor->nombreFin,sus->valor->peso);
        grafoNuevo->insertarArista(sus->valor->nombreFin,sus->valor->nombreInicio,sus->valor->peso);
    }
    this->imprimir=grafoNuevo;
    this->grafoActual="Kruskal";
    update();
}
