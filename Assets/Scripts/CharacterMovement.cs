using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class CharacterMovement : MonoBehaviour
{
    public enum PlayerStatus
    { // 플레이어의 상태를 나타내는 열거체.
        NONE = -1, // 상태 정보 없음.
        MOVE = 0, // 이동 중.
        NUM, // 상태가 몇 종류 있는지 나타낸다(=3).
    };

    public float MoveSpeed = 3.0f;
    public float TurnSpeed = 360.0f;
    public bool ExpertMode;
    public GameObject Map;
    public GameObject ExitButton;
    public Text HintCountText;
    public GameObject RestartButton;
    public GameObject LevelButton;

    PlayerStatus Enum_PS = PlayerStatus.NONE;
    CharacterController CC;
    Vector3 MoveDirection = Vector3.zero;
    Vector3 Gravity = Vector3.zero;
    Vector3 PrevPos;
    Vector3 CurPos;
    int MapHint;

    private void Awake()
    {
        CC = GetComponent<CharacterController>();
    }
    // Start is called before the first frame update
    void Start()
    {
        Gravity.y = -9.8f;
        MapHint = 3;
        //Cursor.lockState = CursorLockMode.Locked;
        Cursor.visible = false;
        Cursor.lockState = CursorLockMode.Confined;
        if(ExpertMode)
        {
            HintCountText.text = "미니맵(M)\n" + "남은 횟수 : " + MapHint; 
        }
    }

    // Update is called once per frame
    void Update()
    {
        CC.Move(Gravity * Time.deltaTime);
        if (Player_Move())
        {
            Enum_PS = PlayerStatus.MOVE;
        }
        else
            Enum_PS = PlayerStatus.NONE;

        if (Input.GetKeyDown(KeyCode.Q))
        {
            OnBlockMove(true);
        }
        if (Input.GetKeyDown(KeyCode.E))
        {
            OnBlockMove(false);
        }
        if (Input.GetKeyDown(KeyCode.R))
        {
            SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex);
        }
        if (Input.GetKeyDown(KeyCode.Escape))
        {
            TogglePauseMenu();
        }
        if (Input.GetKeyDown(KeyCode.M))
        {
            if(ExpertMode && MapHint >0)
            {
                MapHint--;
                ExpertMode = false;
                HintCountText.text = "미니맵(M)\n" + "남은 횟수 : " + MapHint;
                Map.GetComponent<MapManager>().SetVisibleMinimap(true);
                StartCoroutine(OffMinimap());
            }
        }


    }

    private void LateUpdate()
    {
        CurPos = transform.position;
        Map.GetComponent<MapManager>().Map[(int)PrevPos.x, (int)PrevPos.z] = 0;
        Map.GetComponent<MapManager>().Map[(int)CurPos.x, (int)CurPos.z] = 2;


        if (Input.GetButtonDown("Jump"))
        {
            Map.GetComponent<MapManager>().PrintMap();
        }

    }
    private bool Player_Move()
    {

        PrevPos = transform.position;
        MoveDirection = new Vector3(Input.GetAxis("Horizontal"), 0, Input.GetAxis("Vertical"));
        MoveDirection = transform.TransformDirection(MoveDirection);
        MoveDirection *= MoveSpeed;

        transform.Rotate(0f, Input.GetAxis("Mouse X") * TurnSpeed, 0f, Space.World);
        CC.Move(MoveDirection * Time.deltaTime);

        return (MoveDirection.magnitude > 0.1f ? true : false);
    }

    private void OnBlockMove(bool _IsReverseMove)
    {
        if (!(this.GetComponent<RayScript>().GetIsRayHit()))
            return;


        RaycastHit block = this.GetComponent<RayScript>().HitObj;
        bool reverse = _IsReverseMove;
        if (block.transform.CompareTag("Block"))
        {

            BlockDir hitDir = block.transform.gameObject.transform.parent.gameObject.GetComponent<BlockControl>().Dir;
            Vector3 blockTopLeftPos = block.transform.gameObject.transform.parent.gameObject.GetComponent<BlockControl>().TopLeftPivot;
            Vector3 blockTopRightPos = block.transform.gameObject.transform.parent.gameObject.GetComponent<BlockControl>().TopRightPivot;
            Vector3 blockBottomLeftPos = block.transform.gameObject.transform.parent.gameObject.GetComponent<BlockControl>().CurPos;
            Vector3 blockBottomRightPos = block.transform.gameObject.transform.parent.gameObject.GetComponent<BlockControl>().BottomRightPivot;
            Vector3 pos = this.transform.position;
            if (hitDir == BlockDir.Vertical)
            {
                if(pos.x<blockTopLeftPos.x) // 왼쪽
                {
                    if(BetweenFloat(blockBottomLeftPos.z, blockTopLeftPos.z , pos.z))
                    {
                        block.transform.gameObject.transform.parent.gameObject.GetComponent<BlockControl>().Move(!reverse);
                    }
                }
                else if(pos.x>blockTopRightPos.x) //오른쪽
                {
                    if (BetweenFloat(blockBottomLeftPos.z, blockTopLeftPos.z, pos.z))
                    {
                        block.transform.gameObject.transform.parent.gameObject.GetComponent<BlockControl>().Move(reverse);
                    }
                }
                else //가운데
                {
                    if(blockTopLeftPos.z<pos.z) // 가운데 위
                    {
                        block.transform.gameObject.transform.parent.gameObject.GetComponent<BlockControl>().Move(!reverse);
                    }
                    else if (blockBottomLeftPos.z > pos.z) // 가운데 아래
                    {
                        block.transform.gameObject.transform.parent.gameObject.GetComponent<BlockControl>().Move(reverse);
                    }
                }
            }
            else if (hitDir == BlockDir.Horizontal)
            {
                if (pos.x < blockTopLeftPos.x) // 왼쪽
                {
                    if (BetweenFloat(blockBottomLeftPos.z, blockTopLeftPos.z, pos.z))
                    {
                        block.transform.gameObject.transform.parent.gameObject.GetComponent<BlockControl>().Move(reverse);
                    }
                }
                else if (pos.x > blockTopRightPos.x) //오른쪽
                {
                    if (BetweenFloat(blockBottomLeftPos.z, blockTopLeftPos.z, pos.z))
                    {
                        block.transform.gameObject.transform.parent.gameObject.GetComponent<BlockControl>().Move(!reverse);
                    }
                }
                else //가운데
                {
                    if (blockTopLeftPos.z < pos.z) // 가운데 위
                    {
                        block.transform.gameObject.transform.parent.gameObject.GetComponent<BlockControl>().Move(!reverse);
                    }
                    else if (blockBottomLeftPos.z > pos.z) // 가운데 아래
                    {
                        block.transform.gameObject.transform.parent.gameObject.GetComponent<BlockControl>().Move(reverse);
                    }

                }
            }
        }
    }
    public void TogglePauseMenu()
    {
        ExitButton.active = !ExitButton.active;
        LevelButton.active = ExitButton.active;
        RestartButton.active = ExitButton.active;
        Cursor.visible = ExitButton.active; 
    }

    public void QuitGame()
    {
        Application.Quit();
    }

    private bool BetweenFloat(float Min, float Max, float _Input)
    {
        if (_Input < Min) return false;
        if (_Input > Max) return false;

        return true;
    }

    public void LoadLevelScene()
    {
        SceneManager.LoadScene("LevelSelect");
    }

    IEnumerator OffMinimap()
    {
        yield return new WaitForSeconds(3.0f);
        ExpertMode = true;
        Map.GetComponent<MapManager>().SetVisibleMinimap(false);
    }
}
