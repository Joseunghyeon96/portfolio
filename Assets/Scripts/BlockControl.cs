using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public enum BlockDir
{
    NONE = -1,
    Vertical = 0,// 세로
    Horizontal,
    Num
}

public class BlockControl : MonoBehaviour
{
    public enum BlockType
    { // 블럭 타입
        NONE = -1, // 상태 정보 없음.
        FIXED = 0, // 고정.
        ONEWAY, // 단방향
        BIDIRECTION , // 양방향
        NUM, // 상태가 몇 종류 있는지 나타낸다.
    };

    public Vector3 Direction;
    public int BlockWidth;
    public int BlockHeight;
    public BlockType Type;
    public BlockDir Dir;
    public bool bIsMoving;
    public bool NegativeDir;
    MapManager Manager;
    public Vector3 CurPos; // BottomLeftPivot
    public Vector3 BottomRightPivot;
    public Vector3 TopRightPivot;
    public Vector3 TopLeftPivot;
    
    Vector3 NextPos;
    int[,] Map;
    public AudioClip MoveSound;
    AudioSource audioSource;

    // Start is called before the first frame update
    private void Awake()
    {
        this.audioSource = GetComponent<AudioSource>();
    }
    void Start()
    {
        Manager = GameObject.Find("Map").GetComponent<MapManager>();
        Map = Manager.Map;
        CurPos = transform.position;

        for (int i = Mathf.RoundToInt(CurPos.x); i < Mathf.RoundToInt(CurPos.x + BlockWidth); i++)
        {
            for (int j = Mathf.RoundToInt(CurPos.z); j < Mathf.RoundToInt(CurPos.z + BlockHeight); j++)
            {
                Map[i, j] = 1;
            }
        } // 맵 셋팅

        bIsMoving = false;

        BottomRightPivot = CurPos + new Vector3((float)BlockWidth, 0.0f, 0.0f);
        TopRightPivot = CurPos + new Vector3((float)BlockWidth, 0.0f, (float)BlockHeight);
        TopLeftPivot = CurPos + new Vector3(0.0f, 0.0f , (float)BlockHeight);
        audioSource.clip = MoveSound;
    }

    // Update is called once per frame
    void Update()
    {
        if(bIsMoving)
        {
            transform.position = Vector3.MoveTowards(gameObject.transform.position, NextPos, 0.02f);
            if (transform.position == NextPos)
            {
                bIsMoving = false;

                CurPos = transform.position;

                BottomRightPivot = CurPos + new Vector3((float)BlockWidth, 0.0f, 0.0f);
                TopRightPivot = CurPos + new Vector3((float)BlockWidth, 0.0f, (float)BlockHeight);
                TopLeftPivot = CurPos + new Vector3(0.0f, 0.0f, (float)BlockHeight);
                //Debug.Log("Pivot : " + CurPos);
                //Debug.Log("BottomRightPivot : " + BottomRightPivot);
                //Debug.Log("TopLeftPivot : " + TopLeftPivot);
                //Debug.Log("TopRightPivot : " + TopRightPivot);

            }
        }
    }

    public void Move(bool _IsReverseDir)// true면 반대 방향 false면 지정방향
    {
        if (Type == BlockType.FIXED) return; // 고정형블럭
        if (NegativeDir) _IsReverseDir = !_IsReverseDir;
        if (_IsReverseDir && Type == BlockType.ONEWAY) return; // 단방향블럭을 역방향 이동시킬 때
        if (!CanMove(_IsReverseDir)) return;

        for (int i = Mathf.RoundToInt(CurPos.x); i < Mathf.RoundToInt(CurPos.x + BlockWidth); i++)
        {
            for (int j = Mathf.RoundToInt(CurPos.z); j < Mathf.RoundToInt(CurPos.z + BlockHeight); j++)
            {
                Map[i, j] = 0;
            }
        } // 이전에 있던 곳 초기화

        for (int i = Mathf.RoundToInt(NextPos.x); i < Mathf.RoundToInt(NextPos.x + BlockWidth); i++)
        {
            for (int j = Mathf.RoundToInt(NextPos.z); j < Mathf.RoundToInt(NextPos.z + BlockHeight); j++)
            {
                Map[i, j] = 1;
            }
        } // 이동할 곳 맵에 블럭 채워주기

        bIsMoving = true;
        audioSource.Play();
        return;
    }

    private bool CanMove(bool _IsReverseDir) // true면 반대 방향 false면 지정방향
    {
        if (bIsMoving)
            return false; // 이동중이면 

        Vector3 dir = Direction;
        if(_IsReverseDir)
        {
            dir = -dir;
        }
        //CurPos = transform.position;
        NextPos = CurPos + dir;

        if (dir.x == 0) // 세로방향 이동 일경우
        {
            if (dir.z > 0) // 정방향이동
            {
                int j = Mathf.RoundToInt(CurPos.z) + BlockHeight;
                if (j > Manager.Height - 1 || j < 0) // 맵을 세로방향 벗어난경우
                {
                    Debug.Log("Can't Move, Map height over");
                    return false;
                }
                if (Map[Mathf.RoundToInt(CurPos.x), j] != 0) // 이동해야 할곳에 플레이어, 다른블럭이 있는 경우
                {
                    Debug.Log("Can't Move, Map not Y empty");
                    return false;
                }

            }
            else // 역방향이동
            {
                int j = Mathf.RoundToInt(CurPos.z) - 1;
                if (j > Manager.Height - 1 || j < 0) // 맵을 세로방향 벗어난경우
                {
                    Debug.Log("Can't Move, Map height over");
                    return false;
                }

                if (Map[Mathf.RoundToInt(CurPos.x), j] != 0) // 이동해야 할곳에 플레이어, 다른블럭이 있는 경우
                {
                    Debug.Log("Can't Move, Map not Y empty");
                    return false;
                }
            }
        }

        else // 가로방향 이동일 경우
        {
            if (dir.x > 0 ) // 정방향이동
            {
                int i = Mathf.RoundToInt(CurPos.x) + BlockWidth;

                if (i > Manager.Width - 1 || i < 0)  // 맵을 가로방향 벗어난경우
                {
                    Debug.Log("Can't Move, Map width over");
                    return false;
                }
                if (Map[i, Mathf.RoundToInt(CurPos.z)] != 0) // 이동해야 할곳에 플레이어, 다른블럭이 있는 경우
                {
                    Debug.Log("Can't Move, Map not X empty");
                    return false;
                }

            }

            else // 역방향 이동
            {
                int i = Mathf.RoundToInt(CurPos.x) - 1;

                if (i > Manager.Width - 1 || i < 0)  // 맵을 가로방향 벗어난경우
                {
                    Debug.Log("Can't Move, Map width over");
                    return false;
                }
                if (Map[i, Mathf.RoundToInt(CurPos.z)] != 0) // 이동해야 할곳에 플레이어, 다른블럭이 있는 경우
                {
                    Debug.Log("Can't Move, Map not X empty");
                    return false;
                }

            }
        }

        return true;
    }
}
