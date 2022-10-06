# OpenGLFramework
OpenGLを使用した3DCGの基礎的な部分が一旦完了したので、
ゲームフレームワークとして落とし込む作業を行う。
また、これを使用して冬に行われる審査会に向けて3Dゲームを作成する。

## 【ゲーム概要】
・スタートとゴールが設定されておりユーザが任意に道を作成することで攻略する。

・キャラクターはスタート位置からユーザが作成した道を最短経路で自動的に進む。

・作成できる道は平面(XZ軸)だけでなく高さ(Y軸)も作成することが可能で１マスまでなら登れる。

・「進め! キノピオ隊長」を参考に視点も操作して道を作成していくことが可能。

・道中収集物要素を取り入れて最短でゴールするか収集物を集めるかを選択できるようにする。

・道の編集フェーズは制限時間付きで各種コース毎に異なる。
