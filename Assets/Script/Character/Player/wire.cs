using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class wire : MonoBehaviour
{
    GameObject Player;

    Camera mainCam;

    LineRenderer lr;
    GameObject wireStorage;
    bool isWireShoot;
    bool doWireBack;
    Vector3 wire_dir;
    Rigidbody rb;

    float wireDistance;

    KeyCode shoot_wire_key;
    int spacebar_rotation;

    bool isLineRender;

    public static Vector3 rayHitPoint;

    float grabTime;
    bool hitWall;
    public bool isGrabWall;

    Image Aim;

    RaycastHit[] rayHits;

    void Start()
    {
        Player = GameObject.Find("Player").gameObject;
        mainCam = Camera.main;

        if(this.gameObject.name == "LeftWire")
        {
            shoot_wire_key = KeyCode.Q;
            wireStorage = GameObject.Find("LeftWireStorage");
        }
        if(this.gameObject.name == "RightWire")
        {
            shoot_wire_key = KeyCode.E;
            wireStorage = GameObject.Find("RightWireStorage");
        }

        rb = GetComponent<Rigidbody>();      

        //라인 랜더러 초기화
        lr = wireStorage.GetComponent<LineRenderer>();
        lr.SetWidth(0.1f, 0.1f);
        //lr.SetColors(Color.green, Color.green);                    
        lr.enabled = false;
        
        isWireShoot = false;
        doWireBack = false;
        isLineRender = false;
        
        wireDistance = 100.0f;

        grabTime = 0.0f;
        hitWall = false;
        isGrabWall = false;

        Aim = GameObject.Find("Canvas_player").transform.Find("Aim").GetComponent<Image>();
        rayHits = Physics.RaycastAll(Vector3.zero, Vector3.zero, 0);
    }

    void Update()
    {
        //와이어 오브젝트 hit 판정
        CheckWireHit();

        if (!doWireBack && !isGrabWall)
        {
            if (Input.GetKeyDown(KeyCode.Space))
            {
                ////wire 쏘는 방향
                //if (hitWall)
                //    wire_dir = mainCam.transform.position + (mainCam.transform.forward * Vector3.Distance(mainCam.transform.position, rayHitPoint));
                //else
                //    wire_dir = mainCam.transform.position + (mainCam.transform.forward * wireDistance);

                //isWireShoot = true;
                //doWireBack = false;
            }

            if (Input.GetKeyDown(shoot_wire_key))
            {
                rb.velocity = Vector3.zero;
                this.transform.position = wireStorage.transform.position;

                //wire 쏘는 방향
                if (hitWall)
                    wire_dir = rayHitPoint - wireStorage.transform.position;
                else
                    wire_dir = mainCam.transform.position + (mainCam.transform.forward * wireDistance) - wireStorage.transform.position;

                isLineRender = true;
                isWireShoot = true;
                doWireBack = false;

                PlayerAudioSources.Instance.Play(PlayerAudioSources.State.WIRESHOOT);
            }
        }

        ShootWire();
        GrabWall();
        BackWire();

        LineRender(wireStorage, this.gameObject);
        lr.enabled = isLineRender;
    }

    //와이어 쏘는 함수
    void ShootWire()
    {
        // 와이어 박혔을 때 잡고 있는 시간 측정
        if (!isWireShoot) return;

        //와이어 이동
        rb.AddForce(wire_dir * 500.0f);
        isWireShoot = false;
    }

    //와이어로 벽을 잡고 있는 함수
    void GrabWall()
    {
        if (!isGrabWall) return;

        //키를 누르고 있을 때 계속 벽을 잡는다
        if (Input.GetKey(shoot_wire_key))
            grabTime += Time.deltaTime;

        grabTime -= Time.deltaTime;
        Debug.Log(" " + grabTime);
        if (grabTime < 0.0f)
        {
            isGrabWall = false;
            doWireBack = true;
        }

    }

    //와이어 돌아오는 함수
    void BackWire()
    {
        if (!doWireBack) return;

        rb.velocity = Vector3.zero;

        this.transform.position = wireStorage.transform.position;
        grabTime = 0.0f;

        isGrabWall = false;
        isLineRender = false;
        doWireBack = false;
    }

    //라인 그리는 함수
    void LineRender(GameObject start, GameObject end)
    {
        if (!isLineRender) return;
        lr.SetPosition(0, start.transform.position);
        lr.SetPosition(1, end.transform.position);

        if (!isGrabWall && (Vector3.Distance(this.transform.position, wireStorage.transform.position) >= wireDistance - 0.5f))
        {
            doWireBack = true;
        }
    }

    //와이어 쐈을 때 wall에 맞았는지 안 맞았는지 판별 함수
    void CheckWireHit()
    {
        hitWall = false;

        Ray ray;

        //마우스 위치로 ray 쏘기
        ray = mainCam.ScreenPointToRay(Input.mousePosition);
        Aim.color = Color.white;
        Debug.DrawRay(ray.origin, ray.direction * wireDistance, Color.black);

        //Fade Wall 되돌리기
        if (rayHits.Length > 0)
        {
            for (int i = 0; i < rayHits.Length; i++)
            {
                if (!rayHits[i].transform) continue;
                if (rayHits[i].transform.gameObject.tag != "Wall") continue;                
                Color temp = rayHits[i].transform.GetComponent<MeshRenderer>().material.color;
                temp.a = 1.0f;
                rayHits[i].transform.GetComponent<MeshRenderer>().material.color = temp;
            }
        }

        rayHits = Physics.RaycastAll(ray, wireDistance);

        for (int i = 0; i < rayHits.Length; i++)
        {
            if (rayHits[i].transform.gameObject.tag != "Wall") continue;
            //Debug.Log("ray hit : " + Vector3.Distance(mainCam.transform.position, rayHits[i].transform.position));
            //Debug.Log(Vector3.Distance(mainCam.transform.position, Player.transform.position));
            //플레이어와 카메라 사이일 때, Fade Wall
            if (Vector3.Distance(mainCam.transform.position, rayHits[i].transform.position) < 12.0f)
            {
                Color temp = rayHits[i].transform.GetComponent<MeshRenderer>().material.color;
                temp.a = 0.1f;
                rayHits[i].transform.GetComponent<MeshRenderer>().material.color = temp;
            }
            //플레이어와 카메라 사이가 아닐 경우
            else
            {
                rayHitPoint = rayHits[i].point;
                hitWall = true;
                Aim.color = Color.red;
                break;
            }
        }
    }

    //wire가 wall에 부딪혔을 때
    void OnTriggerEnter(Collider collision)
    {
        //와이어가 돌아올 때 작동 X
        if (doWireBack) return;

        //tag가 "wall"인 오브젝트랑 부딪혔을 때
        if (collision.gameObject.tag == "Wall")
        {
            rb.velocity = Vector3.zero;
            this.transform.position = rayHitPoint;
            grabTime = 0.15f;
            isGrabWall = true;
        }
    }
}