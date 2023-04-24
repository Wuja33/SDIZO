#include "RedBlackTree.h"

RedBlackTree::RedBlackTree()
{
    //stra¿nik wskazuje na siebie i ma czarny kolor
    nil.parent = &nil;
    nil.left = &nil;
    nil.right = &nil;
    nil.isRed = false;

    root = &nil;    //na samym pocz¹tku, to straznik jest korzeniem

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

    while(help!=&nil)           //szukaj do momentu a¿ dojdziesz do stra¿nika
    {
        if(key < help->key)                 //jeœli szukany klucz jest mniejszy, ni¿ klucz w wêŸle -> idŸ do lewego poddrzewa
            help = help->left;
        else if (key > help->key)
            help = help->right;             //jeœli szukany klucz jest wiekszy, ni¿ klucz w wêŸle -> idŸ do prawego poddrzewa
        else
        {
            timer.stop();
            return help;                    //jesli równy, to zwroc dany wezel
        }
    }

    timer.stop();
    return nullptr;                         //nie znaleziono takie wêz³a -> zwróæ NULL
}


Node *RedBlackTree::successor(Node *node) {
    Node * help;

    if(node != &nil)                            //jeœli podany wêzê³ nie jest stra¿nikiem, mo¿na kontynuowaæ poszukiwania nastêpnika
    {
        /// PRZYPADEK 1 ///
        //Podany wêze³, posiada prawego syna
        //Nastêpnikiem jest zatem, wêze³ o minimalnym kluczu w poddrzewie prawego syna

        if(node->right != &nil){
            //SZUKANIE MINIMALNEGO WÊZ£A
            node = node->right;
            while (node->left != &nil)  //dopóki nie natrafisz na stra¿nika, przechodŸ do lewego poddrzewa
            {
                node = node->left;
            }
            return node;
        }
        else
        {
            /// PRZYPADEK 2 ///
            //Podany wêze³, NIE posiada prawego syna
            //Szukamy zatem pierwszego ojca, dla którego, nasz wêze³ jest w lewym poddrzewie

            help = node->parent;                            //przypisanie ojca do help
            while(help != &nil && node == help->right)      //dopóki ojciec jest ró¿ny od stra¿nika oraz znajdujemy siê w prawym poddrzewie ojca -> szukaj dalej
            {
                node = help;                                //stary ojciec staje siê synem
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
    if (right != &nil)              //jeœli prawy syn, nie jest stra¿nikiem, czyli czy jest sens robiæ obrót
    {
        node->right = right->left;  //prawym synem wêz³a, zostaje lewy wnuk od prawego syna
        right->left = node;         //lewym synem, starego prawego syna, staje siê wêze³, wed³ug którego obracaliœmy

        parent = node->parent;      //rodzic wêz³a obracanego
        right->parent = parent;     //rodzicem starego prawego syna, staje siê rodzic wêz³a, wed³ug którego obracaliœmy
        node->parent = right;       //rodzicem wêz³a wed³ug którego obracaliœmy, staje siê stary prawy syn

        if (node->right != &nil)    //jeœli lewy wnuk od starego prawego syna, nie by³ stra¿nikiem -> zamieñ jego rodzica, na wêze³ wed³ug którego obracaliœmy
            node->right->parent = node;

        if (parent != &nil)         //jeœli rodzic wêz³a obracanego, nie by³ straŸnikiem, nale¿y dokonaæ korekty
        {
            if (parent->left == node)   //jeœli wêze³ by³ w lewym poddrzewie
                parent->left = right;
            else                        //jeœli wêze³ by³ w prawym poddrzewie
                parent->right = right;
        }
        else                        //jeœli by³ to straŸnik, oznacza to, ¿e by³ to korzeñ -> korekta
            root = right;
    }
}

void RedBlackTree::rotateRight(Node *node) {
    Node* left, *parent;

    left = node->left;
    if (left != &nil)              //jeœli lewy syn, nie jest stra¿nikiem, czyli czy jest sens robiæ obrót
    {
        node->left = left->right;  //lewym synem wêz³a, zostaje prawy wnuk od lewego syna
        left->right = node;        //prawym synem, starego lewego syna, staje siê wêze³, wed³ug którego obracaliœmy

        parent = node->parent;     //rodzic wêz³a obracanego
        left->parent = parent;     //rodzicem starego lewego syna, staje siê rodzic wêz³a, wed³ug którego obracaliœmy
        node->parent = left;       //rodzicem wêz³a wed³ug którego obracaliœmy, staje siê stary lewy syn

        if (node->left != &nil)    //jeœli prawy wnuk od starego lewego syna, nie by³ stra¿nikiem -> zamieñ jego rodzica, na wêze³ wed³ug którego obracaliœmy
            node->left->parent = node;

        if (parent != &nil)         //jeœli rodzic wêz³a obracanego, nie by³ straŸnikiem, nale¿y dokonaæ korekty
        {
            if (parent->left == node)   //jeœli wêze³ by³ w lewym poddrzewie
                parent->left = left;
            else                        //jeœli wêze³ by³ w prawym poddrzewie
                parent->right = left;
        }
        else                        //jeœli by³ to straŸnik, oznacza to, ¿e by³ to korzeñ -> korekta
            root = left;
    }
}

void RedBlackTree::insert(int key) {
    timer.run();

    Node* newNode = new Node(key,root,&nil,&nil);       // tworzenie nowego wêz³a (jego synowie to stra¿nicy, a rodzic na samym poczatku to korzeñ

    if (root == &nil)       //jeœli nie ma korzenia, niech nowy wêze³ nim zostanie
    {
        newNode->isRed = false;
        root = newNode;
    }
    else
    {
        while (true)
        {
            if (newNode->parent->key < key)             //porównywanie kluczy (jeœli wiêkszy -> idŸ do prawego poddrzewa)
            {
                if (newNode->parent->right == &nil)     //jeœli klucz jest wiêkszy, a prawy syn rodzica to stra¿nik -> zast¹p go wstawianym wêz³em
                {
                    newNode->parent->right = newNode;
                    break;                              //element zosta³ wstawiony, mo¿na zakoñczyæ pêtle
                }

                newNode->parent = newNode->parent->right;       //w przeciwnym wypadku, szukaj dalej miejsca w prawym poddrzewie
            }
            else                                        //jeœli nie jest wiêkszy, to oznacza, ¿e jest mniejszy lub równy -> w takim razie, idŸ do lewego poddrzewa
            {
                if (newNode->parent->left == &nil)     //jeœli lewy syn rodzica to stra¿nik -> zast¹p go wstawianym wêz³em
                {
                    newNode->parent->left = newNode;
                    break;                              //element zosta³ wstawiony, mo¿na zakoñczyæ pêtle
                }

                newNode->parent = newNode->parent->left;       //w przeciwnym wypadku, szukaj dalej miejsca w lewym poddrzewie
            }
        }

        /// ELEMENT ZNALAZ£ MIEJSCE

        /// NALE¯Y TERAZ WYKONAÆ EWENTUALNE KOREKTY
        // Zaburzenia w³asnoœci drzewa podczas dodawania to:
        // 1. Korzeñ jest czarny
        // 2. Obydwaj potomkowie czerwonego wêz³a s¹ czarni

        while (newNode->isRed == newNode->parent->isRed && newNode != root)          //dopóki potomek czerwonego wêz³a, bêdzie czerwony oraz nie jest to korzeñ -> wykonuj korekte
        {
            if (newNode->parent == newNode->getGrandFather()->left) //sprawdzenie czy znajdujemy siê w lewym poddrzewie
            {
                ///---------- PRZYPADEK 1  ------------
                //Wuj jest CZERWONY
                //Zamiana kolorów ojca i wuja na CZARNY  oraz  koloru dziadka na CZERWONY

                if (newNode->getUncle()->isRed)             //jeœli wuj jest czerwony
                {
                    newNode->parent->isRed = false;
                    newNode->getUncle()->isRed = false;
                    newNode->getGrandFather()->isRed = true;

                    newNode = newNode->getGrandFather();    //po ca³ej zamianie, nale¿y sprawdziæ, czy po zmianie dziadek nie zaburza w³asnoœci w górnej czêœci
                    continue;
                }

                ///---------- PRZYPADEK 3  ------------
                //Wuj jest CZARNY oraz wêze³ znajduje siê w PRAWYM poddrzewie
                //Rotacja w lewo na ojcu wêz³a, a nastêpnie pojawia siê PRZYPADEK 2

                if (newNode->parent->right == newNode)
                {
                    newNode = newNode->parent;          //operujemy na ojcu
                    rotateLeft(newNode);
                }

                ///---------- PRZYPADEK 2  ------------
                //Wuj jest CZARNY oraz wêze³ znajduje siê w LEWYM poddrzewie
                //Rotacja w prawo na dziadku oraz zamiana koloru ojca i dziadka na przeciwny

                newNode->parent->isRed = !newNode->parent->isRed;                       //negujemy aktualny kolor
                newNode->getGrandFather()->isRed = !newNode->getGrandFather()->isRed;
                rotateRight(newNode->getGrandFather());
            }
            else  //znajdujemy siê w prawym poddrzewie ->> wykonujemy to samo co w lewym, tylko z odbiciem lustrzanym
            {
                ///---------- PRZYPADEK 1  ------------
                //Wuj jest CZERWONY
                //Zamiana kolorów ojca i wuja na CZARNY  oraz  koloru dziadka na CZERWONY

                if (newNode->getUncle()->isRed)             //jeœli wuj jest czerwony
                {
                    newNode->parent->isRed = false;
                    newNode->getUncle()->isRed = false;
                    newNode->getGrandFather()->isRed = true;

                    newNode = newNode->getGrandFather();    //po ca³ej zamianie, nale¿y sprawdziæ, czy po zmianie dziadek nie zaburza w³asnoœci w górnej czêœci
                    continue;
                }

                ///---------- PRZYPADEK 3 (LUSTRZANY) ------------
                //Wuj jest CZARNY oraz wêze³ znajduje siê w LEWYM poddrzewie
                //Rotacja w prawo na ojcu wêz³a, a nastêpnie pojawia siê PRZYPADEK 2

                if (newNode->parent->left == newNode)
                {
                    newNode = newNode->parent;          //operujemy na ojcu
                    rotateRight(newNode);
                }

                ///---------- PRZYPADEK 2 (LUSTRZANY) ------------
                //Wuj jest CZARNY oraz wêze³ znajduje siê w PRAWYM poddrzewie
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
    if(root == nullptr)         //jeœli drzewo jest puste, zakoncz usuwanie
        return;
    timer.run();
    Node* nodeToDelete;
    Node* nodeReplace;

    if (node->left == &nil || node->right == &nil)
        nodeToDelete = node;                                           //jesli usuwany wezel nie ma synow lub ma chocia¿ 1 syna --> usuñ po prostu dany wêze³
    else
        nodeToDelete = successor(node);                                //jesli nie --> szukaj nastêpnika, który bêdzie musia³ zostaæ usuniêty, a nastêpnie wstawiony w jego miejsce

    if (nodeToDelete->left != &nil)
        nodeReplace = nodeToDelete->left;                               //jesli usuwany element ma lewgo syna, ustaw wêze³ zastêpczy jako lewego syna
    else
        nodeReplace = nodeToDelete->right;                              //jesli usuwany element ma prawego syna, ustaw wêze³ zastêpczy jako prawego syna

    nodeReplace->parent = nodeToDelete->parent;                         //korekta rodziców

    if (nodeToDelete == root)
        root = nodeReplace;                                             //ewentualna korekta korzenia
    else if (nodeToDelete == nodeToDelete->parent->left)
        nodeToDelete->parent->left = nodeReplace;                       //korekta rodzica usuwanego wêz³a
    else
        nodeToDelete->parent->right = nodeReplace;

    if (nodeToDelete != node)
        node->key = nodeToDelete->key;                                  //jesli wêze³ usuwany, nie jest tym samym elementem wejœciowym (przypadek z nastêpnikiem) -->> przepisz klucze

    if (!nodeToDelete->isRed) {                                      //jeœli usuwany wêze³ jest czarny --> mog¹ zaistnieæ komplikacje z w³asnoœciami drzewa, a wiêc trzeba je przywróciæ

        /// NAPRAWIANIE W£ASNOŒCI DRZEWA ///

        Node *help;
        while (nodeReplace != root && !nodeReplace->isRed) {            //wykonuj dopóki nie bêdzie to korzeñ, oraz wêze³ nodeReplace nie jest czerwony
            if (nodeReplace == nodeReplace->parent->left) {             //jesli nodeReplace jest lewym synem
                help = nodeReplace->parent->right;                      //ustaw help jako prawego syna nodeReplace
               /// PRZYPADEK 1 ///
               //Brat wêz³a nodeReplace (help) jest CZERWONY
               //Wykonujemy rotacje w lewo oraz zamieniamy kolor ojca nodeReplace na CZERWONY
               //oraz jego dziadka (po rotacji to help) na CZARNY

                if (help->isRed) {
                    help->isRed = false;
                    nodeReplace->parent->isRed = true;
                    rotateLeft(nodeReplace->parent);
                    help = nodeReplace->parent->right;                    //powrót do pocz¹tkowych ustawieñ
                }

                /// PRZYPADEK 2 ///
                //Brat wêz³a nodeReplace (help) jest CZARNY i posiada czarnych synów
                //Zamiana koloru help na CZERWONY oraz przeniesienie naprawy w³asnoœci do ojca nodeReplace

                if (!help->left->isRed && !help->right->isRed) {            //lewy syn i prawy syn s¹ czarni
                    help->isRed = true;
                    nodeReplace = nodeReplace->parent;
                }
                else                                                        //lewy syn lub prawy syn jest czerwony
                {
                    /// PRZYPADEK 3 ///
                    //Brat wêz³a nodeReplace (help) jest CZARNY, a lewy syn help jest CZERWONY, a prawy CZERWONY
                    //Zamiana koloru lewego syna help z help -> syn = CZARNY, help = CZERWONY  , a nastêpnie rotacja w prawo

                    if (!help->right->isRed) {                              //jesli prawy syn jest czarny
                        help->left->isRed = false;
                        help->isRed = true;
                        rotateRight(help);
                        help = nodeReplace->parent->right;                  //powrót do pocz¹tkowych ustawieñ po rotacji, aby móc przejœæ jeszcze do kolejnych przypadków
                    }

                    /// PRZYPADEK 4 ///
                    //Brat wêz³a nodeReplace (help) jest CZARNY, a jego prawy syn jest CZERWONY
                    //Przenosimy kolor z wêz³a ojca nodeReplace do brata nodeReplace (help),
                    //a nastêpnie zamieniamy kolor ojca nodeReplace oraz prawego syna na CZARNY
                    //potem nastêpuje rotacja w lewo

                    help->isRed = nodeReplace->parent->isRed;
                    nodeReplace->parent->isRed = false;
                    help->right->isRed = false;
                    rotateLeft(nodeReplace->parent);


                    nodeReplace = root; //ABY ZAKOÑCZYÆ PÊTLE
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

        //Na sam koniec przypisujemy wstawionemu wêz³owi kolor usuniêtego wêz³a, mianowicie CZARNY
        nodeReplace->isRed = false;
    }
    delete nodeToDelete;
    timer.stop();
}

void RedBlackTree::remove(int key) {
    if(root == nullptr)         //jeœli drzewo jest puste, zakoncz usuwanie
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
        nodeToDelete = node;                                           //jesli usuwany wezel nie ma synow lub ma chocia¿ 1 syna --> usuñ po prostu dany wêze³
    else
        nodeToDelete = successor(node);                                //jesli nie --> szukaj nastêpnika, który bêdzie musia³ zostaæ usuniêty, a nastêpnie wstawiony w jego miejsce

    if (nodeToDelete->left != &nil)
        nodeReplace = nodeToDelete->left;                               //jesli usuwany element ma lewgo syna, ustaw wêze³ zastêpczy jako lewego syna
    else
        nodeReplace = nodeToDelete->right;                              //jesli usuwany element ma prawego syna, ustaw wêze³ zastêpczy jako prawego syna

    nodeReplace->parent = nodeToDelete->parent;                         //korekta rodziców

    if (nodeToDelete == root)
        root = nodeReplace;                                             //ewentualna korekta korzenia
    else if (nodeToDelete == nodeToDelete->parent->left)
        nodeToDelete->parent->left = nodeReplace;                       //korekta rodzica usuwanego wêz³a
    else
        nodeToDelete->parent->right = nodeReplace;

    if (nodeToDelete != node)
        node->key = nodeToDelete->key;                                  //jesli wêze³ usuwany, nie jest tym samym elementem wejœciowym (przypadek z nastêpnikiem) -->> przepisz klucze

    if (!nodeToDelete->isRed) {                                      //jeœli usuwany wêze³ jest czarny --> mog¹ zaistnieæ komplikacje z w³asnoœciami drzewa, a wiêc trzeba je przywróciæ

        /// NAPRAWIANIE W£ASNOŒCI DRZEWA ///

        Node *help;
        while (nodeReplace != root && !nodeReplace->isRed) {//wykonuj dopóki nie bêdzie to korzeñ, oraz wêze³ nodeReplace nie jest czerwony
            if (nodeReplace == nodeReplace->parent->left) {             //jesli nodeReplace jest lewym synem
                help = nodeReplace->parent->right;                      //ustaw help jako prawego syna nodeReplace
                /// PRZYPADEK 1 ///
                //Brat wêz³a nodeReplace (help) jest CZERWONY
                //Wykonujemy rotacje w lewo oraz zamieniamy kolor ojca nodeReplace na CZERWONY
                //oraz jego dziadka (po rotacji to help) na CZARNY

                if (help->isRed) {
                    help->isRed = false;
                    nodeReplace->parent->isRed = true;
                    rotateLeft(nodeReplace->parent);
                    help = nodeReplace->parent->right;                    //powrót do pocz¹tkowych ustawieñ
                }

                /// PRZYPADEK 2 ///
                //Brat wêz³a nodeReplace (help) jest CZARNY i posiada czarnych synów
                //Zamiana koloru help na CZERWONY oraz przeniesienie naprawy w³asnoœci do ojca nodeReplace

                if (!help->left->isRed && !help->right->isRed) {            //lewy syn i prawy syn s¹ czarni
                    help->isRed = true;
                    nodeReplace = nodeReplace->parent;
                }
                else                                                        //lewy syn lub prawy syn jest czerwony
                {
                    /// PRZYPADEK 3 ///
                    //Brat wêz³a nodeReplace (help) jest CZARNY, a lewy syn help jest CZERWONY, a prawy CZERWONY
                    //Zamiana koloru lewego syna help z help -> syn = CZARNY, help = CZERWONY  , a nastêpnie rotacja w prawo

                    if (!help->right->isRed) {                              //jesli prawy syn jest czarny
                        help->left->isRed = false;
                        help->isRed = true;
                        rotateRight(help);
                        help = nodeReplace->parent->right;                  //powrót do pocz¹tkowych ustawieñ po rotacji, aby móc przejœæ jeszcze do kolejnych przypadków
                    }

                    /// PRZYPADEK 4 ///
                    //Brat wêz³a nodeReplace (help) jest CZARNY, a jego prawy syn jest CZERWONY
                    //Przenosimy kolor z wêz³a ojca nodeReplace do brata nodeReplace (help),
                    //a nastêpnie zamieniamy kolor ojca nodeReplace oraz prawego syna na CZARNY
                    //potem nastêpuje rotacja w lewo

                    help->isRed = nodeReplace->parent->isRed;
                    nodeReplace->parent->isRed = false;
                    help->right->isRed = false;
                    rotateLeft(nodeReplace->parent);


                    nodeReplace = root; //ABY ZAKOÑCZYÆ PÊTLE
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

        //Na sam koniec przypisujemy wstawionemu wêz³owi kolor usuniêtego wêz³a, mianowicie CZARNY
        nodeReplace->isRed = false;
    }
    delete nodeToDelete;
    timer.stop();
}

void RedBlackTree::deleteTree(Node* node) {
    if (node != &nil)   //dopokóki wêze³ nie jest straŸnikiem, wykonuj usuwanie
    {
        deleteTree(node->right);
        deleteTree(node->left);
        delete node;
    }
}

Timer RedBlackTree::getTimer() {
    return timer;
}
