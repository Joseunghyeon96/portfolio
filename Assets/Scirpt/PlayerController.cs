using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class PlayerController : MonoBehaviour
{
    public GameObject camera;
    Vector3 PlayerPos;
    Ray ray;
    RaycastHit rayHit;
    GameObject hitObject;

    public GameObject[] Player = new GameObject[3];
    public ParticleSystem[] changeEffect = new ParticleSystem[3];
    public int player_seq;
    public int player_seq_max;
    float change_time;
    public bool canChange;

    public bool stun;
    public bool dead;
    public bool clear;

    GameObject FlashBomb;
    bool flashStun;
    float flashStunTime;
    Image Flash;

    float clearbossTime;

    public bool cameraView;

    public int whatStage;

    void Start()
    {
        player_seq = 0;
        player_seq_max = GameObject.Find("DataController").GetComponent<DataController>().Get_playerSeq();
        change_time = 0.5f;
        canChange = true;
        Player[1].SetActive(false);
        Player[2].SetActive(false);

        stun = false;
        dead = false;
        clear = false;
        flashStun = false;
        flashStunTime = 5.0f;

        whatStage = GameObject.Find("DataController").GetComponent<DataController>().Get_curStage();

        if (whatStage == 3)
        {
            FlashBomb = GameObject.Find("Boss").GetComponent<Boss>().FlashBomb.gameObject;
            Flash = GameObject.Find("UI").transform.Find("Flash").GetComponent<Image>();
            clearbossTime = 5.0f;
        }

        cameraView = false;
    }

    void FixedUpdate()
    {
        if (whatStage == 3 && GameObject.Find("UIController").GetComponent<UIController>().bossStageStart) return;
        if (cameraView) return;
        if (whatStage == 3 && GameObject.Find("Boss").GetComponent<Boss>().bossClear)
        {
            camera.transform.position = new Vector3(GameObject.Find("Boss").transform.position.x + 1,
                GameObject.Find("Boss").transform.position.y + 4, GameObject.Find("Boss").transform.position.z - 8);
            clearbossTime -= Time.deltaTime;
            if (clearbossTime <= 0)
            {
                GameObject.Find("UIController").GetComponent<UIController>().clear = true;
                GameObject.Find("Boss").GetComponent<Boss>().bossClear = false;
            }
            return;
        }
        FadeWall();
        PlayerPos = new Vector3(Player[player_seq].transform.position.x, Player[player_seq].transform.position.y + 4f, Player[player_seq].transform.position.z - 6f);
        camera.transform.position = Vector3.Lerp(camera.transform.position, PlayerPos, Time.deltaTime * 2f);
    }

    void Update()
    {
        if (Input.GetKey(KeyCode.R)) SceneManager.LoadScene("Stage"+whatStage);
        if (Input.GetKey(KeyCode.Escape)) Application.Quit();

        if (whatStage == 3 && (GameObject.Find("Boss").GetComponent<Boss>().bossEnd ||
            GameObject.Find("UIController").GetComponent<UIController>().bossStageStart))
            return;

        if (clear)
        {
            GameObject.Find("DataController").GetComponent<DataController>().Set_StageTime
                (whatStage, GameObject.Find("UIController").GetComponent<UIController>().time);
            if (whatStage < 3)
                GameObject.Find("DataController").GetComponent<DataController>().SetStageOpen(whatStage + 1);
            GameObject.Find("DataController").GetComponent<DataController>().Plus_playerSeq();
            if (whatStage != 3) SceneManager.LoadScene("Clear");
            else SceneManager.LoadScene("End");
        }

        if (flashStun)
        {
            flashStunTime -= Time.deltaTime;
            Color temp = Flash.color;
            temp.a = flashStunTime / 5;
            Flash.color = temp;
            if (flashStunTime <= 0)
            {
                flashStun = false;
                flashStunTime = 5.0f;
            }
        }

        if (!canChange) change_time -= Time.deltaTime;
        if (change_time <= 0.0f)
        {
            canChange = true;
            change_time = 0.5f;
        }

        if (player_seq != 2)
        {
            if (Player[2].GetComponent<SpeedCharacter>().dash <= 10.0f)
                Player[2].GetComponent<SpeedCharacter>().dash += Time.deltaTime;
        }

        if (Input.GetKeyDown(KeyCode.Z) && this.transform.Find("Jump").GetComponent<JumpCharacter>().jumpCount == 2 && canChange)
        {
            if (stun || dead) return;
            GameObject.Find("UIController").GetComponent<UIController>().rotate = true;
            PlayerChange();
        }

        if (Input.GetKeyDown(KeyCode.P))
        {
            if (whatStage != 3)
                Player[player_seq].transform.position = GameObject.Find("MoonStone").transform.position;
            else
                Player[player_seq].transform.position = GameObject.Find("Boss").transform.position;
        }

        if (whatStage == 3 && FlashBomb.GetComponent<Boss_FlashBomb>().explod)
        {
            if (FlashBomb.transform.position.z <= Player[player_seq].transform.position.z + 80 &&
                FlashBomb.transform.position.z >= Player[player_seq].transform.position.z)
            {
                if (Player[player_seq].transform.rotation == Quaternion.Euler(0, 45, 0) ||
                    Player[player_seq].transform.rotation == Quaternion.Euler(0, -45, 0) ||
                    Player[player_seq].transform.rotation == Quaternion.Euler(0, 0, 0))
                {
                    flashStun = true;
                }
            }
            if (FlashBomb.transform.position.z <= Player[player_seq].transform.position.z &&
                FlashBomb.transform.position.z >= Player[player_seq].transform.position.z - 30)
            {
                if (Player[player_seq].transform.rotation == Quaternion.Euler(0, 135, 0) ||
                    Player[player_seq].transform.rotation == Quaternion.Euler(0, -135, 0) ||
                    Player[player_seq].transform.rotation == Quaternion.Euler(0, 180, 0))
                {
                    flashStun = true;
                }
            }

            FlashBomb.GetComponent<Boss_FlashBomb>().explod = false;
        }

        if (Input.GetKeyDown(KeyCode.F10))
        {
            if (cameraView)
            {
                cameraView = false;
                camera.transform.rotation = Quaternion.Euler(20, 0, 0);
            }
            else
            {
                cameraView = true;
                camera.transform.rotation = Quaternion.Euler(40, 0, 0);
                camera.transform.position = new Vector3(11, Player[player_seq].transform.position.y + 30, -20);
            }
        }
        if (cameraView)
        {
            if (Input.GetKey(KeyCode.UpArrow))
            {
                camera.transform.rotation = Quaternion.Euler(0, 0, 0);
                camera.transform.Translate(Vector3.forward * 40.0f * Time.deltaTime);
                camera.transform.rotation = Quaternion.Euler(40, 0, 0);
            }
            if (Input.GetKey(KeyCode.DownArrow))
            {
                camera.transform.rotation = Quaternion.Euler(0, 0, 0);
                camera.transform.Translate(Vector3.back * 40.0f * Time.deltaTime);
                camera.transform.rotation = Quaternion.Euler(40, 0, 0);
            }
        }
    }

    void PlayerChange()
    {
        for (int i = 0; i < player_seq_max + 1; i++)
            if (i != player_seq) Player[i].transform.position = Player[player_seq].transform.position;

        if (player_seq < player_seq_max) player_seq++;
        else player_seq = 0;

        for (int i = 0; i < player_seq_max + 1; i++)
        {
            if (i == player_seq) Player[i].SetActive(true);
            else Player[i].SetActive(false);
        }
        changeEffect[player_seq].Play();

        if (player_seq == 0 && player_seq_max == 2)
        {
            Player[player_seq].GetComponent<JumpCharacter>().moveSpeed = Player[2].GetComponent<SpeedCharacter>().moveSpeed;
            Player[player_seq].GetComponent<JumpCharacter>().isBoost = Player[2].GetComponent<SpeedCharacter>().isBoost;
            Player[player_seq].GetComponent<JumpCharacter>().boostTime = Player[2].GetComponent<SpeedCharacter>().boostTime;
        }
        if (player_seq == 1 && player_seq_max >= 1)
        {
            Player[player_seq].GetComponent<PowerCharacter>().moveSpeed = Player[0].GetComponent<JumpCharacter>().moveSpeed;
            Player[player_seq].GetComponent<PowerCharacter>().isBoost = Player[0].GetComponent<JumpCharacter>().isBoost;
            Player[player_seq].GetComponent<PowerCharacter>().boostTime = Player[0].GetComponent<JumpCharacter>().boostTime;
        }
        if (player_seq == 2)
        {
            Player[player_seq].GetComponent<SpeedCharacter>().moveSpeed = Player[1].GetComponent<PowerCharacter>().moveSpeed;
            Player[player_seq].GetComponent<SpeedCharacter>().isBoost = Player[1].GetComponent<PowerCharacter>().isBoost;
            Player[player_seq].GetComponent<SpeedCharacter>().boostTime = Player[1].GetComponent<PowerCharacter>().boostTime;
        }

        canChange = false;
    }

    void FadeWall()
    {
        ray = Camera.main.ViewportPointToRay(new Vector3(0.5f, 0.4f, 0f));

        if (Physics.Raycast(ray, out rayHit, 5.5f) && rayHit.transform.gameObject.GetComponent<MeshRenderer>() != null
            && rayHit.transform.gameObject.GetComponent<MeshRenderer>().material.color != null)
        {
            hitObject = rayHit.transform.gameObject;
            Color temp = hitObject.GetComponent<MeshRenderer>().material.color;
            temp.a = 0.3f;
            hitObject.GetComponent<MeshRenderer>().material.color = temp;
        }
        else
        {
            if (hitObject != null)
            {
                Color temp = hitObject.GetComponent<MeshRenderer>().material.color;
                temp.a = 1.0f;
                hitObject.GetComponent<MeshRenderer>().material.color = temp;
            }
        }
    }
}