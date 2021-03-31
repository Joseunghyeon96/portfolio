using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class UIController : MonoBehaviour
{
    public Slider remainMap;
    public float endPos;
    float playerPos;

    public Slider remainDash;
    public float dashMax;
    public Image[] runImage = new Image[6];
    int run_seq;
    float runImage_time;
    public Image monsterImage;
    public Image bossImage;

    public Text Timer;
    public float time;

    public GameObject[] WhatPlayer = new GameObject[3];
    public Image[] whatPlayer = new Image[3];
    public bool rotate;
    float rotateVal;
    int playerMax;

    public GameObject GameOver;
    public Image OverBack;
    float over_seq;

    public GameObject FinishPortal;
    float portal_seq;
    public Text GameClear;
    public bool clear;

    public GameObject NPC;
    bool npcEffect;

    float bossCreateTime;
    public bool bossStageStart;
    public GameObject bossFail;
    public GameObject Key;
    float bossFailTime;

    void Start()
    {
        dashMax = 10.0f;
        run_seq = 1;
        runImage_time = 0.2f;

        time = 0.0f;

        RotatePlayerImageSeting();

        GameClear.enabled = false;
        npcEffect = true;

        over_seq = 0;
        portal_seq = 0;
        clear = false;

        if (NPC != null)
            NPC.SetActive(false);

        bossCreateTime = 5.5f;
        bossStageStart = true;
        bossFailTime = 0.0f;

        if (GameObject.Find("DataController").GetComponent<DataController>().Get_playerSeq() == 2)
            remainDash.gameObject.SetActive(true);
    }

    void Update()
    {
        if (GameObject.Find("DataController").GetComponent<DataController>().Get_curStage() == 3 && bossStageStart)
            BossCreate();
        //보스 클리어
        if (GameObject.Find("DataController").GetComponent<DataController>().Get_curStage() == 3 &&
            GameObject.Find("Boss").GetComponent<Boss>().bossEnd)
        {
            bossFail.SetActive(true);
            bossFailTime += Time.deltaTime;
            Color temp = bossFail.GetComponent<Image>().color;
            temp.a = bossFailTime / 4;
            if (bossFailTime >= 4) SceneManager.LoadScene("Fail");
            return;
        }

        //죽었을 때
        if (GameObject.Find("Player").GetComponent<PlayerController>().dead)
        {
            GameOver.SetActive(true);
            over_seq += Time.deltaTime;
            OverBack.color = new Color(0, 0, 0, over_seq / 4);
            if (over_seq / 4 >= 1f) SceneManager.LoadScene("Fail");
            return;
        }

        //클리어 했을 때
        if (clear)
        {
            if (GameObject.Find("DataController").GetComponent<DataController>().Get_curStage() != 3)
            {
                NPC.GetComponent<Animator>().SetBool("speak", false);
                if (npcEffect)
                {
                    GameClear.enabled = true;
                    FinishPortal.SetActive(true);
                    NPC.SetActive(true);
                    NPC.GetComponent<Animator>().SetBool("speak", true);
                    npcEffect = false;
                }
            }
            else
            {
                if (npcEffect)
                {
                    GameClear.enabled = true;
                    FinishPortal.SetActive(true);
                    GameObject.Find("Player").GetComponent<PlayerController>().Player
                        [GameObject.Find("Player").GetComponent<PlayerController>().player_seq].transform.position = new Vector3(11, 10.1f, 780);
                    npcEffect = false;
                    Key.SetActive(true);
                }
            }
            portal_seq += Time.deltaTime;
            FinishPortal.transform.rotation = Quaternion.Euler(portal_seq * 100, -90, 90);
            if (portal_seq >= 3.0f) GameClear.enabled = false;
            return;
        }

        #region 타이머
        time += Time.deltaTime;
        if ((int)time % 60 < 10) Timer.text = "" + (int)time / 60 + " : 0" + (int)time % 60;
        else Timer.text = "" + (int)time / 60 + " : " + (int)time % 60;
        #endregion

        #region 슬라이더
        //대쉬
        if (remainDash.gameObject.activeSelf == true)
            remainDash.value = GameObject.Find("Player").transform.Find("Speed").GetComponent<SpeedCharacter>().dash / dashMax;
        //맵
        playerPos = GameObject.Find("Player").GetComponent<PlayerController>().Player
           [GameObject.Find("Player").GetComponent<PlayerController>().player_seq].transform.position.z;
        remainMap.value = playerPos / endPos;
        //달리는 이미지
        RunImage();
        #endregion

        //플레이어 회전 이미지
        RotatePlayerImage();
    }

    void RotatePlayerImage()
    {
        if (!rotate || playerMax == 0) return;

        if (playerMax == 1)
        {
            WhatPlayer[1].transform.rotation = Quaternion.Euler(0, rotateVal, 0);
            rotateVal += 30;

            if (GameObject.Find("Player").GetComponent<PlayerController>().player_seq == 1)
            {
                if (rotateVal == 210)
                {
                    rotate = false;
                    whatPlayer[1].transform.SetAsLastSibling();
                    return;
                }
            }

            else if (GameObject.Find("Player").GetComponent<PlayerController>().player_seq == 0)
            {
                if (rotateVal == 390)
                {
                    rotateVal = 0;
                    rotate = false;
                    whatPlayer[0].transform.SetAsLastSibling();
                    return;
                }
            }
        }

        if (playerMax == 2)
        {
            WhatPlayer[2].transform.rotation = Quaternion.Euler(0, rotateVal, 0);
            for (int i = 0; i < 3; i++)
                whatPlayer[i].gameObject.SetActive(true);
            rotateVal += 20;

            if (GameObject.Find("Player").GetComponent<PlayerController>().player_seq == 1)
            {
                if (rotateVal == 140)
                {
                    rotate = false;
                    whatPlayer[1].transform.SetAsLastSibling();
                    return;
                }
            }

            else if (GameObject.Find("Player").GetComponent<PlayerController>().player_seq == 2)
            {
                if (rotateVal == 260)
                {
                    rotate = false;
                    whatPlayer[2].transform.SetAsLastSibling();
                    return;
                }
            }

            else if (GameObject.Find("Player").GetComponent<PlayerController>().player_seq == 0)
            {
                if (rotateVal == 380)
                {
                    rotateVal = 0;
                    rotate = false;
                    whatPlayer[0].transform.SetAsLastSibling();
                    return;
                }
            }
        }
    }

    void RotatePlayerImageSeting()
    {
        playerMax = GameObject.Find("DataController").GetComponent<DataController>().Get_playerSeq();

        rotate = false;
        rotateVal = 0;

        if (playerMax == 0)
        {
            WhatPlayer[0].SetActive(true);
            WhatPlayer[1].SetActive(false);
            WhatPlayer[2].SetActive(false);
        }

        if (playerMax == 1)
        {
            WhatPlayer[1].SetActive(true);
            WhatPlayer[0].SetActive(false);
            WhatPlayer[2].SetActive(false);

            whatPlayer[0] = WhatPlayer[1].transform.Find("Jump").GetComponent<Image>();
            whatPlayer[1] = WhatPlayer[1].transform.Find("Power").GetComponent<Image>();
        }

        if (playerMax == 2)
        {
            WhatPlayer[2].SetActive(true);
            WhatPlayer[0].SetActive(false);
            WhatPlayer[1].SetActive(false);

            whatPlayer[0] = WhatPlayer[2].transform.Find("Jump").GetComponent<Image>();
            whatPlayer[1] = WhatPlayer[2].transform.Find("Power").GetComponent<Image>();
            whatPlayer[2] = WhatPlayer[2].transform.Find("Speed").GetComponent<Image>();
        }
    }

    void RunImage()
    {
        runImage[0].transform.position = new Vector3(510 + remainMap.value * 900, 142, 0);
        if (GameObject.Find("DataController").GetComponent<DataController>().Get_curStage() != 3)
        {
            float monsterPos = GameObject.Find("FollowMonster").transform.position.z * 1.85f;
            monsterImage.transform.position = new Vector3(490 + monsterPos, 142, 0);
        }
        else
        {
            float bossPos = GameObject.Find("Boss").transform.position.z * 1.14f;
            bossImage.transform.position = new Vector3(520 + bossPos, 142, 0);
            float monsterPos = GameObject.Find("FollowMonster").transform.position.z * 1.14f;
            monsterImage.transform.position = new Vector3(490 + monsterPos, 142, 0);
        }

        runImage_time -= Time.deltaTime;
        if (runImage_time > 0.0f) return;

        if (run_seq < 5) run_seq++;
        else run_seq = 1;
        runImage[0].sprite = runImage[run_seq].sprite;
        runImage_time = 0.2f;
    }

    void BossCreate()
    {
        bossCreateTime -= Time.deltaTime;

        if (bossCreateTime <= 0)
        {
            GameObject.Find("UI").transform.Find("BossExplain").gameObject.SetActive(false);
            bossStageStart = false;
        }
    }
}