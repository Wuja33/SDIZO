#include "RedBlackTree.h"

RedBlackTree::RedBlackTree()
{
    //stra�nik wskazuje na siebie i ma czarny kolor
    nil.parent = &nil;
    nil.left = &nil;
    nil.right = &nil;
    nil.isRed = false;

    root = &nil;    //na samym pocz�tku, to straznik jest korzeniem

    cr = cl = cp = "  ";
    cr [ 0 ] = 218; cr [ 1 ] = 196;
    cl [ 0 ] = 192; cl [ 1 ] = 196;
    cp [ 0 ] = 179;
}

RedBlackTree::~RedBlackTree() {
    deleteTree(root);
}

void RedBlackTree::printRBT(string sp, string sn, Node * p){
    string t;

    if( p != &nil )
    {
        t = sp;
        if( sn == cr ) t [ t.length( ) - 2 ] = ' ';
        printRBT ( t+cp, cr, p->right );

        t = t.substr ( 0, sp.length( ) - 2 );
        if (p->isRed)
            cout << t << sn << "R" << ":" << p->key << endl;
        else
            cout << t << sn << "B" << ":" << p->key << endl;

        t = sp;
        if( sn == cl ) t [ t.length( ) - 2 ] = ' ';
        printRBT ( t+cp, cl, p->left );
    }
}

void RedBlackTree::print() {
    printRBT ( "", "", root );
}

Node *RedBlackTree::search(int key) {
    timer.run();
    Node* help = root;          //zaczynamy poszukiwania od korzenia

    while(help!=&nil)           //szukaj do momentu a� dojdziesz do stra�nika
    {
        if(key < help->key)                 //je�li szukany klucz jest mniejszy, ni� klucz w w�le -> id� do lewego poddrzewa
            help = help->left;
        else if (key > help->key)
            help = help->right;             //je�li szukany klucz jest wiekszy, ni� klucz w w�le -> id� do prawego poddrzewa
        else
        {
            timer.stop();
            return help;                    //jesli r�wny, to zwroc dany wezel
        }
    }

    timer.stop();
    return nullptr;                         //nie znaleziono takie w�z�a -> zwr�� NULL
}


Node *RedBlackTree::successor(Node *node) {
    Node * help;

    if(node != &nil)                            //je�li podany w�z� nie jest stra�nikiem, mo�na kontynuowa� poszukiwania nast�pnika
    {
        /// PRZYPADEK 1 ///
        //Podany w�ze�, posiada prawego syna
        //Nast�pnikiem jest zatem, w�ze� o minimalnym kluczu w poddrzewie prawego syna

        if(node->right != &nil){
            //SZUKANIE MINIMALNEGO W�Z�A
            node = node->right;
            while (node->left != &nil)  //dop�ki nie natrafisz na stra�nika, przechod� do lewego poddrzewa
            {
                node = node->left;
            }
            return node;
        }
        else
        {
            /// PRZYPADEK 2 ///
            //Podany w�ze�, NIE posiada prawego syna
            //Szukamy zatem pierwszego ojca, dla kt�rego, nasz w�ze� jest w lewym poddrzewie

            help = node->parent;                            //przypisanie ojca do help
            while(help != &nil && node == help->right)      //dop�ki ojciec jest r�ny od stra�nika oraz znajdujemy si� w prawym poddrzewie ojca -> szukaj dalej
            {
                node = help;                                //stary ojciec staje si� synem
                help = help->parent;                        //kolejny ojciec (dziadek poprzedniego)
            }
            return help;
        }
    }

    return &nil;
}

void RedBlackTree::rotateLeft(Node *node) {
    Node* right, *parent;

    right = node->right;
    if (right != &nil)              //je�li prawy syn, nie jest stra�nikiem, czyli czy jest sens robi� obr�t
    {
        node->right = right->left;  //prawym synem w�z�a, zostaje lewy wnuk od prawego syna
        right->left = node;         //lewym synem, starego prawego syna, staje si� w�ze�, wed�ug kt�rego obracali�my

        parent = node->parent;      //rodzic w�z�a obracanego
        right->parent = parent;     //rodzicem starego prawego syna, staje si� rodzic w�z�a, wed�ug kt�rego obracali�my
        node->parent = right;       //rodzicem w�z�a wed�ug kt�rego obracali�my, staje si� stary prawy syn

        if (node->right != &nil)    //je�li lewy wnuk od starego prawego syna, nie by� stra�nikiem -> zamie� jego rodzica, na w�ze� wed�ug kt�rego obracali�my
            node->right->parent = node;

        if (parent != &nil)         //je�li rodzic w�z�a obracanego, nie by� stra�nikiem, nale�y dokona� korekty
        {
            if (parent->left == node)   //je�li w�ze� by� w lewym poddrzewie
                parent->left = right;
            else                        //je�li w�ze� by� w prawym poddrzewie
                parent->right = right;
        }
        else                        //je�li by� to stra�nik, oznacza to, �e by� to korze� -> korekta
            root = right;
    }
}

void RedBlackTree::rotateRight(Node *node) {
    Node* left, *parent;

    left = node->left;
    if (left != &nil)              //je�li lewy syn, nie jest stra�nikiem, czyli czy jest sens robi� obr�t
    {
        node->left = left->right;  //lewym synem w�z�a, zostaje prawy wnuk od lewego syna
        left->right = node;        //prawym synem, starego lewego syna, staje si� w�ze�, wed�ug kt�rego obracali�my

        parent = node->parent;     //rodzic w�z�a obracanego
        left->parent = parent;     //rodzicem starego lewego syna, staje si� rodzic w�z�a, wed�ug kt�rego obracali�my
        node->parent = left;       //rodzicem w�z�a wed�ug kt�rego obracali�my, staje si� stary lewy syn

        if (node->left != &nil)    //je�li prawy wnuk od starego lewego syna, nie by� stra�nikiem -> zamie� jego rodzica, na w�ze� wed�ug kt�rego obracali�my
            node->left->parent = node;

        if (parent != &nil)         //je�li rodzic w�z�a obracanego, nie by� stra�nikiem, nale�y dokona� korekty
        {
            if (parent->left == node)   //je�li w�ze� by� w lewym poddrzewie
                parent->left = left;
            else                        //je�li w�ze� by� w prawym poddrzewie
                parent->right = left;
        }
        else                        //je�li by� to stra�nik, oznacza to, �e by� to korze� -> korekta
            root = left;
    }
}

void RedBlackTree::insert(int key) {
    timer.run();

    Node* newNode = new Node(key,root,&nil,&nil);       // tworzenie nowego w�z�a (jego synowie to stra�nicy, a rodzic na samym poczatku to korze�

    if (root == &nil)       //je�li nie ma korzenia, niech nowy w�ze� nim zostanie
    {
        newNode->isRed = false;
        root = newNode;
    }
    else
    {
        while (true)
        {
            if (newNode->parent->key < key)             //por�wnywanie kluczy (je�li wi�kszy -> id� do prawego poddrzewa)
            {
                if (newNode->parent->right == &nil)     //je�li klucz jest wi�kszy, a prawy syn rodzica to stra�nik -> zast�p go wstawianym w�z�em
                {
                    newNode->parent->right = newNode;
                    break;                              //element zosta� wstawiony, mo�na zako�czy� p�tle
                }

                newNode->parent = newNode->parent->right;       //w przeciwnym wypadku, szukaj dalej miejsca w prawym poddrzewie
            }
            else                                        //je�li nie jest wi�kszy, to oznacza, �e jest mniejszy lub r�wny -> w takim razie, id� do lewego poddrzewa
            {
                if (newNode->parent->left == &nil)     //je�li lewy syn rodzica to stra�nik -> zast�p go wstawianym w�z�em
                {
                    newNode->parent->left = newNode;
                    break;                              //element zosta� wstawiony, mo�na zako�czy� p�tle
                }

                newNode->parent = newNode->parent->left;       //w przeciwnym wypadku, szukaj dalej miejsca w lewym poddrzewie
            }
        }

        /// ELEMENT ZNALAZ� MIEJSCE

        /// NALE�Y TERAZ WYKONA� EWENTUALNE KOREKTY
        // Zaburzenia w�asno�ci drzewa podczas dodawania to:
        // 1. Korze� jest czarny
        // 2. Obydwaj potomkowie czerwonego w�z�a s� czarni

        while (newNode->isRed == newNode->parent->isRed && newNode != root)          //dop�ki potomek czerwonego w�z�a, b�dzie czerwony oraz nie jest to korze� -> wykonuj korekte
        {
            if (newNode->parent == newNode->getGrandFather()->left) //sprawdzenie czy znajdujemy si� w lewym poddrzewie
            {
                ///---------- PRZYPADEK 1  ------------
                //Wuj jest CZERWONY
                //Zamiana kolor�w ojca i wuja na CZARNY  oraz  koloru dziadka na CZERWONY

                if (newNode->getUncle()->isRed)             //je�li wuj jest czerwony
                {
                    newNode->parent->isRed = false;
                    newNode->getUncle()->isRed = false;
                    newNode->getGrandFather()->isRed = true;

                    newNode = newNode->getGrandFather();    //po ca�ej zamianie, nale�y sprawdzi�, czy po zmianie dziadek nie zaburza w�asno�ci w g�rnej cz�ci
                    continue;
                }

                ///---------- PRZYPADEK 3  ------------
                //Wuj jest CZARNY oraz w�ze� znajduje si� w PRAWYM poddrzewie
                //Rotacja w lewo na ojcu w�z�a, a nast�pnie pojawia si� PRZYPADEK 2

                if (newNode->parent->right == newNode)
                {
                    newNode = newNode->parent;          //operujemy na ojcu
                    rotateLeft(newNode);
                }

                ///---------- PRZYPADEK 2  ------------
                //Wuj jest CZARNY oraz w�ze� znajduje si� w LEWYM poddrzewie
                //Rotacja w prawo na dziadku oraz zamiana koloru ojca i dziadka na przeciwny

                newNode->parent->isRed = !newNode->parent->isRed;                       //negujemy aktualny kolor
                newNode->getGrandFather()->isRed = !newNode->getGrandFather()->isRed;
                rotateRight(newNode->getGrandFather());
            }
            else  //znajdujemy si� w prawym poddrzewie ->> wykonujemy to samo co w lewym, tylko z odbiciem lustrzanym
            {
                ///---------- PRZYPADEK 1  ------------
                //Wuj jest CZERWONY
                //Zamiana kolor�w ojca i wuja na CZARNY  oraz  koloru dziadka na CZERWONY

                if (newNode->getUncle()->isRed)             //je�li wuj jest czerwony
                {
                    newNode->parent->isRed = false;
                    newNode->getUncle()->isRed = false;
                    newNode->getGrandFather()->isRed = true;

                    newNode = newNode->getGrandFather();    //po ca�ej zamianie, nale�y sprawdzi�, czy po zmianie dziadek nie zaburza w�asno�ci w g�rnej cz�ci
                    continue;
                }

                ///---------- PRZYPADEK 3 (LUSTRZANY) ------------
                //Wuj jest CZARNY oraz w�ze� znajduje si� w LEWYM poddrzewie
                //Rotacja w prawo na ojcu w�z�a, a nast�pnie pojawia si� PRZYPADEK 2

                if (newNode->parent->left == newNode)
                {
                    newNode = newNode->parent;          //operujemy na ojcu
                    rotateRight(newNode);
                }

                ///---------- PRZYPADEK 2 (LUSTRZANY) ------------
                //Wuj jest CZARNY oraz w�ze� znajduje si� w PRAWYM poddrzewie
                //Rotacja w lewo na dziadku oraz zamiana koloru ojca i dziadka na przeciwny

                newNode->parent->isRed = !newNode->parent->isRed;                       //negujemy aktualny kolor
                newNode->getGrandFather()->isRed = !newNode->getGrandFather()->isRed;

                rotateLeft(newNode->getGrandFather());
            }
        }
        root->isRed = false;  //korekta korzenia
    }
    timer.stop();
}

void RedBlackTree::remove(Node *node) {
    if(root == nullptr)         //je�li drzewo jest puste, zakoncz usuwanie
        return;
    timer.run();
    Node* nodeToDelete;
    Node* nodeReplace;

    if (node->left == &nil || node->right == &nil)
        nodeToDelete = node;                                           //jesli usuwany wezel nie ma synow lub ma chocia� 1 syna --> usu� po prostu dany w�ze�
    else
        nodeToDelete = successor(node);                                //jesli nie --> szukaj nast�pnika, kt�ry b�dzie musia� zosta� usuni�ty, a nast�pnie wstawiony w jego miejsce

    if (nodeToDelete->left != &nil)
        nodeReplace = nodeToDelete->left;                               //jesli usuwany element ma lewgo syna, ustaw w�ze� zast�pczy jako lewego syna
    else
        nodeReplace = nodeToDelete->right;                              //jesli usuwany element ma prawego syna, ustaw w�ze� zast�pczy jako prawego syna

    nodeReplace->parent = nodeToDelete->parent;                         //korekta rodzic�w

    if (nodeToDelete == root)
        root = nodeReplace;                                             //ewentualna korekta korzenia
    else if (nodeToDelete == nodeToDelete->parent->left)
        nodeToDelete->parent->left = nodeReplace;                       //korekta rodzica usuwanego w�z�a
    else
        nodeToDelete->parent->right = nodeReplace;

    if (nodeToDelete != node)
        node->key = nodeToDelete->key;                                  //jesli w�ze� usuwany, nie jest tym samym elementem wej�ciowym (przypadek z nast�pnikiem) -->> przepisz klucze

    if (!nodeToDelete->isRed) {                                      //je�li usuwany w�ze� jest czarny --> mog� zaistnie� komplikacje z w�asno�ciami drzewa, a wi�c trzeba je przywr�ci�

        /// NAPRAWIANIE W�ASNO�CI DRZEWA ///

        Node *help;
        while (nodeReplace != root && !nodeReplace->isRed) {            //wykonuj dop�ki nie b�dzie to korze�, oraz w�ze� nodeReplace nie jest czerwony
            if (nodeReplace == nodeReplace->parent->left) {             //jesli nodeReplace jest lewym synem
                help = nodeReplace->parent->right;                      //ustaw help jako prawego syna nodeReplace
               /// PRZYPADEK 1 ///
               //Brat w�z�a nodeReplace (help) jest CZERWONY
               //Wykonujemy rotacje w lewo oraz zamieniamy kolor ojca nodeReplace na CZERWONY
               //oraz jego dziadka (po rotacji to help) na CZARNY

                if (help->isRed) {
                    help->isRed = false;
                    nodeReplace->parent->isRed = true;
                    rotateLeft(nodeReplace->parent);
                    help = nodeReplace->parent->right;                    //powr�t do pocz�tkowych ustawie�
                }

                /// PRZYPADEK 2 ///
                //Brat w�z�a nodeReplace (help) jest CZARNY i posiada czarnych syn�w
                //Zamiana koloru help na CZERWONY oraz przeniesienie naprawy w�asno�ci do ojca nodeReplace

                if (!help->left->isRed && !help->right->isRed) {            //lewy syn i prawy syn s� czarni
                    help->isRed = true;
                    nodeReplace = nodeReplace->parent;
                }
                else                                                        //lewy syn lub prawy syn jest czerwony
                {
                    /// PRZYPADEK 3 ///
                    //Brat w�z�a nodeReplace (help) jest CZARNY, a lewy syn help jest CZERWONY, a prawy CZERWONY
                    //Zamiana koloru lewego syna help z help -> syn = CZARNY, help = CZERWONY  , a nast�pnie rotacja w prawo

                    if (!help->right->isRed) {                              //jesli prawy syn jest czarny
                        help->left->isRed = false;
                        help->isRed = true;
                        rotateRight(help);
                        help = nodeReplace->parent->right;                  //powr�t do pocz�tkowych ustawie� po rotacji, aby m�c przej�� jeszcze do kolejnych przypadk�w
                    }

                    /// PRZYPADEK 4 ///
                    //Brat w�z�a nodeReplace (help) jest CZARNY, a jego prawy syn jest CZERWONY
                    //Przenosimy kolor z w�z�a ojca nodeReplace do brata nodeReplace (help),
                    //a nast�pnie zamieniamy kolor ojca nodeReplace oraz prawego syna na CZARNY
                    //potem nast�puje rotacja w lewo

                    help->isRed = nodeReplace->parent->isRed;
                    nodeReplace->parent->isRed = false;
                    help->right->isRed = false;
                    rotateLeft(nodeReplace->parent);


                    nodeReplace = root; //ABY ZAKO�CZY� P�TLE
                }
            }
            else
            {  /// PRZYPADEK LUSTRZANY ///
                help = nodeReplace->parent->left;

                if (help->isRed) {
                    help->isRed = false;
                    nodeReplace->parent->isRed = true;
                    rotateRight(nodeReplace->parent);
                    help = nodeReplace->parent->left;
                }

                if (help->right->isRed && help->left->isRed) {
                    help->isRed = true;
                    nodeReplace = nodeReplace->parent;
                }

                else
                {
                    if (help->left->isRed) {
                        help->right->isRed = false;
                        help->isRed = true;
                        rotateLeft(help);
                        help = nodeReplace->parent->left;
                    }

                    help->isRed = nodeReplace->parent->isRed;
                    nodeReplace->parent->isRed = false;
                    help->left->isRed = false;
                    rotateRight(nodeReplace->parent);
                    nodeReplace = root;
                }
            }
        }

        //Na sam koniec przypisujemy wstawionemu w�z�owi kolor usuni�tego w�z�a, mianowicie CZARNY
        nodeReplace->isRed = false;
    }
    delete nodeToDelete;
    timer.stop();
}

void RedBlackTree::remove(int key) {
    if(root == nullptr)         //je�li drzewo jest puste, zakoncz usuwanie
        return;
    timer.run();
    Node* node = search(key);
    if (node == nullptr)
    {
        timer.stop();
        return;
    }
    Node* nodeToDelete;
    Node* nodeReplace;

    if (node->left == &nil || node->right == &nil)
        nodeToDelete = node;                                           //jesli usuwany wezel nie ma synow lub ma chocia� 1 syna --> usu� po prostu dany w�ze�
    else
        nodeToDelete = successor(node);                                //jesli nie --> szukaj nast�pnika, kt�ry b�dzie musia� zosta� usuni�ty, a nast�pnie wstawiony w jego miejsce

    if (nodeToDelete->left != &nil)
        nodeReplace = nodeToDelete->left;                               //jesli usuwany element ma lewgo syna, ustaw w�ze� zast�pczy jako lewego syna
    else
        nodeReplace = nodeToDelete->right;                              //jesli usuwany element ma prawego syna, ustaw w�ze� zast�pczy jako prawego syna

    nodeReplace->parent = nodeToDelete->parent;                         //korekta rodzic�w

    if (nodeToDelete == root)
        root = nodeReplace;                                             //ewentualna korekta korzenia
    else if (nodeToDelete == nodeToDelete->parent->left)
        nodeToDelete->parent->left = nodeReplace;                       //korekta rodzica usuwanego w�z�a
    else
        nodeToDelete->parent->right = nodeReplace;

    if (nodeToDelete != node)
        node->key = nodeToDelete->key;                                  //jesli w�ze� usuwany, nie jest tym samym elementem wej�ciowym (przypadek z nast�pnikiem) -->> przepisz klucze

    if (!nodeToDelete->isRed) {                                      //je�li usuwany w�ze� jest czarny --> mog� zaistnie� komplikacje z w�asno�ciami drzewa, a wi�c trzeba je przywr�ci�

        /// NAPRAWIANIE W�ASNO�CI DRZEWA ///

        Node *help;
        while (nodeReplace != root && !nodeReplace->isRed) {//wykonuj dop�ki nie b�dzie to korze�, oraz w�ze� nodeReplace nie jest czerwony
            if (nodeReplace == nodeReplace->parent->left) {             //jesli nodeReplace jest lewym synem
                help = nodeReplace->parent->right;                      //ustaw help jako prawego syna nodeReplace
                /// PRZYPADEK 1 ///
                //Brat w�z�a nodeReplace (help) jest CZERWONY
                //Wykonujemy rotacje w lewo oraz zamieniamy kolor ojca nodeReplace na CZERWONY
                //oraz jego dziadka (po rotacji to help) na CZARNY

                if (help->isRed) {
                    help->isRed = false;
                    nodeReplace->parent->isRed = true;
                    rotateLeft(nodeReplace->parent);
                    help = nodeReplace->parent->right;                    //powr�t do pocz�tkowych ustawie�
                }

                /// PRZYPADEK 2 ///
                //Brat w�z�a nodeReplace (help) jest CZARNY i posiada czarnych syn�w
                //Zamiana koloru help na CZERWONY oraz przeniesienie naprawy w�asno�ci do ojca nodeReplace

                if (!help->left->isRed && !help->right->isRed) {            //lewy syn i prawy syn s� czarni
                    help->isRed = true;
                    nodeReplace = nodeReplace->parent;
                }
                else                                                        //lewy syn lub prawy syn jest czerwony
                {
                    /// PRZYPADEK 3 ///
                    //Brat w�z�a nodeReplace (help) jest CZARNY, a lewy syn help jest CZERWONY, a prawy CZERWONY
                    //Zamiana koloru lewego syna help z help -> syn = CZARNY, help = CZERWONY  , a nast�pnie rotacja w prawo

                    if (!help->right->isRed) {                              //jesli prawy syn jest czarny
                        help->left->isRed = false;
                        help->isRed = true;
                        rotateRight(help);
                        help = nodeReplace->parent->right;                  //powr�t do pocz�tkowych ustawie� po rotacji, aby m�c przej�� jeszcze do kolejnych przypadk�w
                    }

                    /// PRZYPADEK 4 ///
                    //Brat w�z�a nodeReplace (help) jest CZARNY, a jego prawy syn jest CZERWONY
                    //Przenosimy kolor z w�z�a ojca nodeReplace do brata nodeReplace (help),
                    //a nast�pnie zamieniamy kolor ojca nodeReplace oraz prawego syna na CZARNY
                    //potem nast�puje rotacja w lewo

                    help->isRed = nodeReplace->parent->isRed;
                    nodeReplace->parent->isRed = false;
                    help->right->isRed = false;
                    rotateLeft(nodeReplace->parent);


                    nodeReplace = root; //ABY ZAKO�CZY� P�TLE
                }
            }
            else
            {  /// PRZYPADEK LUSTRZANY ///
                help = nodeReplace->parent->left;

                if (help->isRed) {
                    help->isRed = false;
                    nodeReplace->parent->isRed = true;
                    rotateRight(nodeReplace->parent);
                    help = nodeReplace->parent->left;
                }

                if (help->right->isRed && help->left->isRed) {
                    help->isRed = true;
                    nodeReplace = nodeReplace->parent;
                }

                else
                {
                    if (help->left->isRed) {
                        help->right->isRed = false;
                        help->isRed = true;
                        rotateLeft(help);
                        help = nodeReplace->parent->left;
                    }

                    help->isRed = nodeReplace->parent->isRed;
                    nodeReplace->parent->isRed = false;
                    help->left->isRed = false;
                    rotateRight(nodeReplace->parent);
                    nodeReplace = root;
                }
            }
        }

        //Na sam koniec przypisujemy wstawionemu w�z�owi kolor usuni�tego w�z�a, mianowicie CZARNY
        nodeReplace->isRed = false;
    }
    delete nodeToDelete;
    timer.stop();
}

void RedBlackTree::deleteTree(Node* node) {
    if (node != &nil)   //dopok�ki w�ze� nie jest stra�nikiem, wykonuj usuwanie
    {
        deleteTree(node->right);
        deleteTree(node->left);
        delete node;
    }
}

Timer RedBlackTree::getTimer() {
    return timer;
}
