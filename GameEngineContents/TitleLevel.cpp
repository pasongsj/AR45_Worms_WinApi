#include "TitleLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCore.h>

#include "TitleBack.h"
#include "PlayLevel.h"


TitleLevel::TitleLevel() 
{

}

TitleLevel::~TitleLevel() 
{

}

void TitleLevel::SoundLoad()
{
    GameEngineDirectory Dir;
    Dir.MoveParentToDirectory("ContentsResources");
    Dir.Move("ContentsResources");
    Dir.Move("Sound");

    std::vector<GameEngineFile> Files = Dir.GetAllFile();

    for (size_t i = 0; i < Files.size(); i++)
    {
        GameEngineResources::GetInst().SoundLoad(Files[i].GetFullPath());
    }

}

void TitleLevel::Loading()
{
    SoundLoad();

	GameEngineDirectory Dir1;
	Dir1.MoveParentToDirectory("ContentsResources");
	Dir1.Move("ContentsResources");
	Dir1.Move("Image");
	Dir1.Move("Title");

    GameEngineDirectory Dir;
    Dir.MoveParentToDirectory("ContentsResources");
    Dir.Move("ContentsResources");
    Dir.Move("Image");
    Dir.Move("Play");

    GameEngineDirectory InterFace;
    InterFace.MoveParentToDirectory("ContentsResources");
    InterFace.Move("ContentsResources");
    InterFace.Move("Image");
    InterFace.Move("InterFace");

    GameEngineDirectory Dir2;
    Dir2.MoveParentToDirectory("ContentsResources");
    Dir2.Move("ContentsResources");
    Dir2.Move("Image");
    Dir2.Move("Title");


	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir1.GetPlusFileName("Intro_Logo.BMP"));
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir1.GetPlusFileName("BackGround.BMP"));
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir1.GetPlusFileName("Title_Backdrop.BMP"));
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir1.GetPlusFileName("Title_Logo.BMP"));
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir1.GetPlusFileName("TitleLogo_Actor.BMP"));
		Image->Cut(5, 1);
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir1.GetPlusFileName("Fade_White.BMP"));
	}

	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir1.GetPlusFileName("Armageddon_1.BMP"));
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir1.GetPlusFileName("Armageddon_2.BMP"));
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir1.GetPlusFileName("Armageddon_3.BMP"));
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir1.GetPlusFileName("Armageddon_4.BMP"));
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir1.GetPlusFileName("Armageddon_5.BMP"));
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir1.GetPlusFileName("Armageddon_6.BMP"));
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir1.GetPlusFileName("Armageddon_7.BMP"));
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir1.GetPlusFileName("Armageddon_8.BMP"));
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir1.GetPlusFileName("Armageddon_9.BMP"));
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir1.GetPlusFileName("Armageddon_10.BMP"));
	}

    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir1.GetPlusFileName("testEnding.BMP"));
    }
	
    {
        Dir.Move("Map");

        //Map & ColMap
        GameEngineImage* MapImage1 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MapCity.bmp"));
        GameEngineImage* ColMapImage1 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MapCity_Ground.bmp"));

        GameEngineImage* MapImage2 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MapBooks.bmp"));
        GameEngineImage* ColMapImage2 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MapBooks_Ground.bmp"));

        GameEngineImage* MapImage3 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MapCars.bmp"));
        GameEngineImage* ColMapImage3 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MapCars_Ground.bmp"));

        GameEngineImage* MapImage4 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MapTrain.bmp"));
        GameEngineImage* ColMapImage4 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MapTrain_Ground.bmp"));

        //BackGround
        GameEngineImage* sky = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("gradient.bmp"));

        GameEngineImage* Water = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Under_Water.bmp"));

        GameEngineImage* Wave = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Water_sprite.bmp"));
        Wave->Cut(1, 11);

        //Map Objects
        GameEngineImage* MapObj1 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MapObject1.bmp"));
        GameEngineImage* MapObjCol1 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MapObject1_Col.bmp"));

        GameEngineImage* MapObj2 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MapObject2.bmp"));
        GameEngineImage* MapObjCol2 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MapObject2_Col.bmp"));

        GameEngineImage* MapObj3 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MapObject3.bmp"));
        GameEngineImage* MapObjCol3 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MapObject3_Col.bmp"));
    }
    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ScatterLeaf.bmp"));
        Image->Cut(5, 3);
    }
    Dir.MoveParent();
    //ItemImage
    {
        Dir.Move("item");
        {

            GameEngineImage* Medikit = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("mcrate1.bmp"));
            Medikit->Cut(1, 12);

            GameEngineImage* FlyingMedikit = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("mcrate2.bmp"));
            FlyingMedikit->Cut(1, 20);

            GameEngineImage* OilDrum1 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("oildrum1.bmp"));
            OilDrum1->Cut(1, 20);

            GameEngineImage* OilDrum2 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("oildrum2.bmp"));
            OilDrum2->Cut(1, 20);

            GameEngineImage* OilDrum3 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("oildrum3.bmp"));
            OilDrum3->Cut(1, 20);

            GameEngineImage* OilDrum4 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("oildrum4.bmp"));
            OilDrum4->Cut(1, 20);

            //Petroleum Effect
            GameEngineImage* Petrol30 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("petrol30.bmp"));
            Petrol30->Cut(1, 20);

            GameEngineImage* Petrol40 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("petrol40.bmp"));
            Petrol40->Cut(1, 20);
        }

        Dir.MoveParent();
    }

    {
        Dir.Move("Weapon");

        GameEngineImage* bazooka = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("bazooka.bmp"));
        GameEngineImage* bazookaRot = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("bazookaRot.bmp"));

        GameEngineImage* Airplane = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Airplane.bmp"));
        GameEngineImage* AirplaneRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("AirplaneRight.bmp"));


        GameEngineImage* sheepWalkRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("sheepWalkRight.bmp"));
        sheepWalkRight->Cut(1, 8);
        GameEngineImage* sheepWalkLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("sheepWalkLeft.bmp"));
        sheepWalkLeft->Cut(1, 8);

        GameEngineImage* AirMissile = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("AirMissile.bmp"));
        GameEngineImage* AirMissileRot = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("AirMissileRot.bmp"));


        GameEngineImage* HomingBlue = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("HomingBlue.bmp"));
        GameEngineImage* HomingRed = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("HomingRed.bmp"));
        GameEngineImage* HomingRot = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("HomingRot.bmp"));

        GameEngineImage* fire = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Fire.bmp"));
        GameEngineImage* marker = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("marker.bmp"));
        marker->Cut(1, 10);

        GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("AimingLine.bmp"));
        GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("AimingLineRot.bmp"));
        GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TempBomb.bmp"));
        GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Grenade.bmp"));
        GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("GrenadeRot.bmp"));
        GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Clusterbomb.bmp"));
        GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ClusterbombRot.bmp"));
        GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("cluster.bmp"));
        GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("clusterRot.bmp"));
        GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Donkey.bmp"));

        GameEngineImage* CarpetTruckLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("CarpetTruckLeft.bmp"));
        CarpetTruckLeft->Cut(1, 4);
        GameEngineImage* CarpetTruckRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("CarpetTruckRight.bmp"));
        CarpetTruckRight->Cut(1, 4);

        GameEngineImage* Carpet = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Carpet.bmp"));
        Carpet->Cut(1, 10);

        //무기 효과
        Dir.Move("Effect");
        {
            GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TimerBack.bmp"));
            GameEngineImage* BazSmoke = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("BazSmoke.bmp"));
            BazSmoke->Cut(1, 64);

            GameEngineImage* Charging = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Charging.bmp"));
            Charging->Cut(1, 16);

            GameEngineImage* circle25 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("circle25.bmp"));
            circle25->Cut(1, 8);
            GameEngineImage* circle50 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("circle50.bmp"));
            circle50->Cut(1, 9);
            GameEngineImage* circle75 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("circle75.bmp"));
            circle75->Cut(1, 4);
            GameEngineImage* circle100 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("circle100.bmp"));
            circle100->Cut(1, 4);

            GameEngineImage* elipse25 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("elipse25.bmp"));
            elipse25->Cut(1, 20);
            GameEngineImage* elipse50 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("elipse50.bmp"));
            elipse50->Cut(1, 20);
            GameEngineImage* elipse75 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("elipse75.bmp"));
            elipse75->Cut(1, 10);
            GameEngineImage* elipse100 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("elipse100.bmp"));
            elipse100->Cut(1, 10);

            GameEngineImage* Smoke50 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Smoke50.bmp"));
            Smoke50->Cut(1, 28);

            GameEngineImage* Smoke100 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Smoke100.bmp"));
            Smoke100->Cut(1, 28);

            GameEngineImage* Poot = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Poot.bmp"));
            Poot->Cut(1, 18);

            GameEngineImage* Spark1 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Spark1.bmp"));
            Spark1->Cut(1, 32);

            GameEngineImage* Spark2 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Spark2.bmp"));
            Spark2->Cut(1, 32);

            GameEngineImage* Biff = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Biff.bmp"));
            Biff->Cut(1, 12);

            GameEngineImage* Pow = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Pow.bmp"));
            Pow->Cut(1, 18);

            GameEngineImage* ChargeAni = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ChargeAni.bmp"));
            ChargeAni->Cut(1, 16);

            GameEngineImage* starSmoke = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("starEffect.bmp"));
            starSmoke->Cut(1, 10);

            GameEngineImage* FireHit = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("firehit.bmp"));
            FireHit->Cut(1, 9);

            GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ChargeAniRot.bmp"));

            Dir.MoveParent();
        }


        Dir.MoveParent();
    }
    {
        Dir.Move("Player");
        Dir.Move("Image");
        {
            //Grave 이미지
            GameEngineImage* Grave1 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Grave1.bmp"));
            Grave1->Cut(1, 20);
            GameEngineImage* Grave2 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Grave2.bmp"));
            Grave2->Cut(1, 20);
            GameEngineImage* Grave3 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Grave3.bmp"));
            Grave3->Cut(1, 20);
            GameEngineImage* Grave4 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Grave4.bmp"));
            Grave4->Cut(1, 20);
            GameEngineImage* Grave5 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Grave5.bmp"));
            Grave5->Cut(1, 20);
            GameEngineImage* Grave6 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Grave6.bmp"));
            Grave6->Cut(1, 20);
        }
        {
            //플레이어 이미지
            GameEngineImage* FacePlant = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FacePlant.bmp"));
            FacePlant->Cut(1, 49);
        }
        {
            //Left 플레이어 이미지
            GameEngineImage* IdleLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("IdleLeft.bmp"));
            IdleLeft->Cut(1, 6);
            GameEngineImage* WalkLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("WalkLeft.bmp"));
            WalkLeft->Cut(1, 15);
            GameEngineImage* JumpReadyLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("JumpReadyLeft.bmp"));
            JumpReadyLeft->Cut(1, 10);
            GameEngineImage* DieLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("DieLeft.bmp"));
            DieLeft->Cut(1, 60);
            GameEngineImage* WinLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("WinLeft.bmp"));
            WinLeft->Cut(1, 14);

            GameEngineImage* AngryLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("AngryLeft.bmp"));
            AngryLeft->Cut(1, 17);

            GameEngineImage* FlyUpLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FlyupLeft.bmp"));
            FlyUpLeft->Cut(1, 2);
            GameEngineImage* FlyLinkLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FlyLinkLeft.bmp"));
            FlyLinkLeft->Cut(1, 7);
            GameEngineImage* FlyDownLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FlydownLeft.bmp"));
            FlyDownLeft->Cut(1, 2);

            GameEngineImage* FlyAwayLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FlyAwayLeft.bmp"));
            FlyAwayLeft->Cut(1, 32);
            GameEngineImage* SlideLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SlideLeft.bmp"));
            SlideLeft->Cut(1, 3);
            GameEngineImage* StandUpLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("StandUpLeft.bmp"));
            StandUpLeft->Cut(1, 22);

            GameEngineImage* bazAimLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("bazAimLeft.bmp"));
            bazAimLeft->Cut(1, 32);
            GameEngineImage* bazOffLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("bazOffLeft.bmp"));
            bazOffLeft->Cut(1, 7);
            GameEngineImage* bazOnLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("bazOnLeft.bmp"));
            bazOnLeft->Cut(1, 8);

            GameEngineImage* sheepOffLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("sheepOffLeft.bmp"));
            sheepOffLeft->Cut(1, 10);
            GameEngineImage* sheepOnLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("sheepOnLeft.bmp"));
            sheepOnLeft->Cut(1, 10);

            GameEngineImage* AirStrikeOffLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("AirStrikeOffLeft.bmp"));
            AirStrikeOffLeft->Cut(1, 10);
            GameEngineImage* AirStrikeOnLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("AirStrikeOnLeft.bmp"));
            AirStrikeOnLeft->Cut(1, 10);

            GameEngineImage* homingAimLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("homingAimLeft.bmp"));
            homingAimLeft->Cut(1, 32);
            GameEngineImage* homingOffLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("homingOffLeft.bmp"));
            homingOffLeft->Cut(1, 7);
            GameEngineImage* homingOnLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("homingOnLeft.bmp"));
            homingOnLeft->Cut(1, 7);

            GameEngineImage* GrenadeAimLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("GrenadeAimLeft.bmp"));
            GrenadeAimLeft->Cut(1, 32);
            GameEngineImage* GrenadeOffLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("GrenadeOffLeft.bmp"));
            GrenadeOffLeft->Cut(1, 10);
            GameEngineImage* GrenadeOnLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("GrenadeOnLeft.bmp"));
            GrenadeOnLeft->Cut(1, 10);

            GameEngineImage* TorchFireLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TorchFireLeft.bmp"));
            TorchFireLeft->Cut(1, 15);
            GameEngineImage* TorchOffLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TorchOffLeft.bmp"));
            TorchOffLeft->Cut(1, 15);
            GameEngineImage* TorchOnLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TorchOnLeft.bmp"));
            TorchOnLeft->Cut(1, 15);

            GameEngineImage* DrillLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("DrillLeft.bmp"));
            DrillLeft->Cut(1, 4);
            GameEngineImage* DrillOffLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("DrillOffLeft.bmp"));
            DrillOffLeft->Cut(1, 13);
            GameEngineImage* DrillOnLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("DrillOnLeft.bmp"));
            DrillOnLeft->Cut(1, 13);

            GameEngineImage* UziAimLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("UziAimLeft.bmp"));
            UziAimLeft->Cut(1, 32);
            GameEngineImage* UziFireLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("UziFireLeft.bmp"));
            UziFireLeft->Cut(1, 32);
            GameEngineImage* UziOffLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("UziOffLeft.bmp"));
            UziOffLeft->Cut(1, 10);
            GameEngineImage* UziOnLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("UziOnLeft.bmp"));
            UziOnLeft->Cut(1, 10);

            GameEngineImage* ClusterBombAimLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ClusterBombAimLeft.bmp"));
            ClusterBombAimLeft->Cut(1, 32);
            //GameEngineImage* ClusterBombFireLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ClusterBombFireLeft.bmp"));
            //ClusterBombFireLeft->Cut(1, 32);
            GameEngineImage* ClusterBombOffLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ClusterBombOffLeft.bmp"));
            ClusterBombOffLeft->Cut(1, 10);
            GameEngineImage* ClusterBombOnLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ClusterBombOnLeft.bmp"));
            ClusterBombOnLeft->Cut(1, 10);

            GameEngineImage* HandgunAimLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("HandgunAimLeft.bmp"));
            HandgunAimLeft->Cut(1, 32);
            GameEngineImage* HandgunFireLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("HandgunFireLeft.bmp"));
            HandgunFireLeft->Cut(1, 32);
            GameEngineImage* HandgunOffLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("HandgunOffLeft.bmp"));
            HandgunOffLeft->Cut(1, 10);
            GameEngineImage* HandgunOnLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("HandgunOnLeft.bmp"));
            HandgunOnLeft->Cut(1, 10);

            GameEngineImage* MinigunAimLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MinigunAimLeft.bmp"));
            MinigunAimLeft->Cut(1, 32);
            GameEngineImage* MinigunFireLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MinigunFireLeft.bmp"));
            MinigunFireLeft->Cut(1, 32);
            GameEngineImage* MinigunOffLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MinigunOffLeft.bmp"));
            MinigunOffLeft->Cut(1, 10);
            GameEngineImage* MinigunOnLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MinigunOnLeft.bmp"));
            MinigunOnLeft->Cut(1, 10);

            GameEngineImage* ShotgunAimLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ShotgunAimLeft.bmp"));
            ShotgunAimLeft->Cut(1, 32);
            GameEngineImage* ShotgunFireLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ShotgunFireLeft.bmp"));
            ShotgunFireLeft->Cut(1, 32);
            GameEngineImage* ShotgunOffLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ShotgunOffLeft.bmp"));
            ShotgunOffLeft->Cut(1, 10);
            GameEngineImage* ShotgunOnLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ShotgunOnLeft.bmp"));
            ShotgunOnLeft->Cut(1, 10);

            GameEngineImage* FirePunchChargingLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FirePunchChargingLeft.bmp"));
            FirePunchChargingLeft->Cut(1, 9);
            GameEngineImage* FirePunchFireLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FirePunchFireLeft.bmp"));
            FirePunchFireLeft->Cut(1, 3);
            GameEngineImage* FirePunchOffLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FirePunchOffLeft.bmp"));
            FirePunchOffLeft->Cut(1, 26);
            GameEngineImage* FirePunchOnLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FirePunchOnLeft.bmp"));
            FirePunchOnLeft->Cut(1, 26);
            GameEngineImage* FirePunchAfterLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FirePunchAfterLeft.bmp"));
            FirePunchAfterLeft->Cut(1, 13);

            GameEngineImage* CarpetOffLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("CarpetOffLeft.bmp"));
            CarpetOffLeft->Cut(1, 10);
            GameEngineImage* CarpetOnLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("CarpetOnLeft.bmp"));
            CarpetOnLeft->Cut(1, 10);

            GameEngineImage* DonkeyOffLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("DonkeyOffLeft.bmp"));
            DonkeyOffLeft->Cut(1, 10);
            GameEngineImage* DonkeyOnLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("DonkeyOnLeft.bmp"));
            DonkeyOnLeft->Cut(1, 10);
        }

        {
            //Right 플레이어 이미지
            GameEngineImage* IdleRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("IdleRight.bmp"));
            IdleRight->Cut(1, 6);
            GameEngineImage* WalkRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("WalkRight.bmp"));
            WalkRight->Cut(1, 15);
            GameEngineImage* JumpReadyRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("JumpReadyRight.bmp"));
            JumpReadyRight->Cut(1, 10);
            GameEngineImage* DieRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("DieRight.bmp"));
            DieRight->Cut(1, 60);
            GameEngineImage* WinRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("WinRight.bmp"));
            WinRight->Cut(1, 14);
            GameEngineImage* FlyUpRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FlyupRight.bmp"));
            FlyUpRight->Cut(1, 2);
            GameEngineImage* FlyLinkRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FlyLinkRight.bmp"));
            FlyLinkRight->Cut(1, 7);
            GameEngineImage* FlyDownRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FlydownRight.bmp"));
            FlyDownRight->Cut(1, 2);
            GameEngineImage* AngryRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("AngryRight.bmp"));
            AngryRight->Cut(1, 17);

            GameEngineImage* FlyAwayRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FlyAwayRight.bmp"));
            FlyAwayRight->Cut(1, 32);
            GameEngineImage* SlideRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SlideRight.bmp"));
            SlideRight->Cut(1, 3);
            GameEngineImage* StandUpRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("StandUpRight.bmp"));
            StandUpRight->Cut(1, 22);

            GameEngineImage* bazAimRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("bazAimRight.bmp"));
            bazAimRight->Cut(1, 32);
            GameEngineImage* bazOffRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("bazOffRight.bmp"));
            bazOffRight->Cut(1, 7);
            GameEngineImage* bazOnRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("bazOnRight.bmp"));
            bazOnRight->Cut(1, 8);

            GameEngineImage* sheepOffRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("sheepOffRight.bmp"));
            sheepOffRight->Cut(1, 10);
            GameEngineImage* sheepOnRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("sheepOnRight.bmp"));
            sheepOnRight->Cut(1, 10);

            GameEngineImage* AirStrikeOffRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("AirStrikeOffRight.bmp"));
            AirStrikeOffRight->Cut(1, 10);
            GameEngineImage* AirStrikeOnRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("AirStrikeOnRight.bmp"));
            AirStrikeOnRight->Cut(1, 10);

            GameEngineImage* homingAimRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("homingAimRight.bmp"));
            homingAimRight->Cut(1, 32);
            GameEngineImage* homingOffRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("homingOffRight.bmp"));
            homingOffRight->Cut(1, 7);
            GameEngineImage* homingOnRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("homingOnRight.bmp"));
            homingOnRight->Cut(1, 7);

            GameEngineImage* GrenadeAimRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("GrenadeAimRight.bmp"));
            GrenadeAimRight->Cut(1, 32);
            GameEngineImage* GrenadeOffRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("GrenadeOffRight.bmp"));
            GrenadeOffRight->Cut(1, 10);
            GameEngineImage* GrenadeOnRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("GrenadeOnRight.bmp"));
            GrenadeOnRight->Cut(1, 10);

            GameEngineImage* TorchFireRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TorchFireRight.bmp"));
            TorchFireRight->Cut(1, 15);
            GameEngineImage* TorchOffRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TorchOffRight.bmp"));
            TorchOffRight->Cut(1, 15);
            GameEngineImage* TorchOnRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TorchOnRight.bmp"));
            TorchOnRight->Cut(1, 15);


            GameEngineImage* DrillRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("DrillRight.bmp"));
            DrillRight->Cut(1, 4);
            GameEngineImage* DrillOffRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("DrillOffRight.bmp"));
            DrillOffRight->Cut(1, 13);
            GameEngineImage* DrillOnRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("DrillOnRight.bmp"));
            DrillOnRight->Cut(1, 13);


            GameEngineImage* UziAimRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("UziAimRight.bmp"));
            UziAimRight->Cut(1, 32);
            GameEngineImage* UziFireRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("UziFireRight.bmp"));
            UziFireRight->Cut(1, 32);
            GameEngineImage* UziOffRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("UziOffRight.bmp"));
            UziOffRight->Cut(1, 10);
            GameEngineImage* UziOnRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("UziOnRight.bmp"));
            UziOnRight->Cut(1, 10);


            GameEngineImage* ClusterBombAimRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ClusterBombAimRight.bmp"));
            ClusterBombAimRight->Cut(1, 32);
            //GameEngineImage* ClusterBombFireRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ClusterBombFireRight.bmp"));
            //ClusterBombireRight->Cut(1, 32);
            GameEngineImage* ClusterBombOffRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ClusterBombOffRight.bmp"));
            ClusterBombOffRight->Cut(1, 10);
            GameEngineImage* ClusterBombOnRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ClusterBombOnRight.bmp"));
            ClusterBombOnRight->Cut(1, 10);

            GameEngineImage* HandgunAimRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("HandgunAimRight.bmp"));
            HandgunAimRight->Cut(1, 32);
            GameEngineImage* HandgunFireRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("HandgunFireRight.bmp"));
            HandgunFireRight->Cut(1, 32);
            GameEngineImage* HandgunOffRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("HandgunOffRight.bmp"));
            HandgunOffRight->Cut(1, 10);
            GameEngineImage* HandgunOnRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("HandgunOnRight.bmp"));
            HandgunOnRight->Cut(1, 10);

            GameEngineImage* MinigunAimRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MinigunAimRight.bmp"));
            MinigunAimRight->Cut(1, 32);
            GameEngineImage* MinigunFireRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MinigunFireRight.bmp"));
            MinigunFireRight->Cut(1, 32);
            GameEngineImage* MinigunOffRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MinigunOffRight.bmp"));
            MinigunOffRight->Cut(1, 10);
            GameEngineImage* MinigunOnRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MinigunOnRight.bmp"));
            MinigunOnRight->Cut(1, 10);

            GameEngineImage* ShotgunAimRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ShotgunAimRight.bmp"));
            ShotgunAimRight->Cut(1, 32);
            GameEngineImage* ShotgunFireRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ShotgunFireRight.bmp"));
            ShotgunFireRight->Cut(1, 32);
            GameEngineImage* ShotgunOffRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ShotgunOffRight.bmp"));
            ShotgunOffRight->Cut(1, 10);
            GameEngineImage* ShotgunOnRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ShotgunOnRight.bmp"));
            ShotgunOnRight->Cut(1, 10);

            GameEngineImage* FirePunchChargingRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FirePunchChargingRight.bmp"));
            FirePunchChargingRight->Cut(1, 9);
            GameEngineImage* FirePunchFireRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FirePunchFireRight.bmp"));
            FirePunchFireRight->Cut(1, 3);
            GameEngineImage* FirePunchOffRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FirePunchOffRight.bmp"));
            FirePunchOffRight->Cut(1, 26);
            GameEngineImage* FirePunchOnRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FirePunchOnRight.bmp"));
            FirePunchOnRight->Cut(1, 26);
            GameEngineImage* FirePunchAfterRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FirePunchAfterRight.bmp"));
            FirePunchAfterRight->Cut(1, 13);

            GameEngineImage* CarpetOffRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("CarpetOffRight.bmp"));
            CarpetOffRight->Cut(1, 10);
            GameEngineImage* CarpetOnRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("CarpetOnRight.bmp"));
            CarpetOnRight->Cut(1, 10);

            GameEngineImage* DonkeyOffRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("DonkeyOffRight.bmp"));
            DonkeyOffRight->Cut(1, 10);
            GameEngineImage* DonkeyOnRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("DonkeyOnRight.bmp"));
            DonkeyOnRight->Cut(1, 10);

        }
        Dir.MoveParent();
    }
    {
        Dir.Move("UIImage");
        {
            //플레이어 UI 이미지
            //본인 캐릭턴에 상단 화살표 이미지
            GameEngineImage* BlueArrowImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("PlayerSelectArrowBlue.bmp"));
            BlueArrowImage->Cut(1, 30);
            GameEngineImage* GreenArrowImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("PlayerSelectArrowGreen.bmp"));
            GreenArrowImage->Cut(1, 30);
            GameEngineImage* MintArrowImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("PlayerSelectArrowMint.bmp"));
            MintArrowImage->Cut(1, 30);
            GameEngineImage* PinkArrowImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("PlayerSelectArrowPink.bmp"));
            PinkArrowImage->Cut(1, 30);
            GameEngineImage* RedArrowImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("PlayerSelectArrowRed.bmp"));
            RedArrowImage->Cut(1, 30);
            GameEngineImage* YellowArrowImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("PlayerSelectArrowYellow.bmp"));
            YellowArrowImage->Cut(1, 30);

            //캐릭터 체력 렌더 이미지
            GameEngineImage* BlueNumberImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("BlueNumberRender.bmp"));
            BlueNumberImage->Cut(10, 1);
            GameEngineImage* GreenNumberImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("GreenNumberRender.bmp"));
            GreenNumberImage->Cut(10, 1);
            GameEngineImage* MintNumberImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MintNumberRender.bmp"));
            MintNumberImage->Cut(10, 1);
            GameEngineImage* RedNumberImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("RedNumberRender.bmp"));
            RedNumberImage->Cut(10, 1);
            GameEngineImage* PinkNumberImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("PinkNumberRender.bmp"));
            PinkNumberImage->Cut(10, 1);
            GameEngineImage* YellowNumberImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("YellowNumberRender.bmp"));
            YellowNumberImage->Cut(10, 1);

            //캐릭터 네임태그 이미지
            GameEngineImage* GreenNametagImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("GreenNameTag.bmp"));
            GameEngineImage* YellowNametagImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("YellowNameTag.bmp"));
            GameEngineImage* PinkNametagImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("PinkNameTag.bmp"));
            GameEngineImage* MintNametagImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MintNameTag.bmp"));
            GameEngineImage* RedNametagImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("RedNameTag.bmp"));
            GameEngineImage* BlueNametagImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("BlueNameTag.bmp"));

            //캐릭터 체력 백그라운드 이미지
            GameEngineImage* PlayerHPBackgroundImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("PlayerHPBackground.bmp"));

            //캐릭터 무적 이미지
            GameEngineImage* PlayerPowerOverwhelmingImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("PowerOverwhelming.bmp"));

            Dir.MoveParent();
        }
        Dir.MoveParent();
        Dir.Move("Etc");
        {
            GameEngineImage* win = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("win.bmp"));
            GameEngineImage* draw = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("draw.bmp"));
        }
        //UI
        {
            {
                GameEngineImage* WaeponInterface = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("weaponSheet.bmp"));
            }
            {
                GameEngineImage* WaeponInterface = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("2020.bmp"));
            }
            {
                GameEngineImage* WaeponInterface = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("WeaponIcon.bmp"));
            }
            {
                GameEngineImage* WaeponInterface = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("bazookaUI.bmp"));
            }
            {
                GameEngineImage* WaeponInterface = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("clusterUI.bmp"));
            }
            {
                GameEngineImage* WaeponInterface = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("grenadeUI.bmp"));
            }
            {
                GameEngineImage* WaeponInterface = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("shotgunUI.bmp"));
            }
            {
                GameEngineImage* WaeponInterface = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("airstrkeUI.bmp"));
            }
            {
                GameEngineImage* WaeponInterface = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("torchUI.bmp"));
            }
            {
                GameEngineImage* WaeponInterface = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("minigunUI.bmp"));
            }
            {
                GameEngineImage* WaeponInterface = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("sheepUI.bmp"));
            }
            {
                GameEngineImage* WaeponInterface = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("hmissileUI.bmp"));
            }
            {
                GameEngineImage* WaeponInterface = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("handgunUI.bmp"));
            }
            {
                GameEngineImage* WaeponInterface = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("uziUI.bmp"));
            }
            {
                GameEngineImage* WaeponInterface = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("firepnch.bmp"));
            }
            {
                GameEngineImage* WaeponInterface = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("drill.bmp"));
            }
            {
                GameEngineImage* WaeponInterface = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("X.bmp"));
            }
            {
                GameEngineImage* WaeponInterface = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("carpet1.bmp"));
            }
            {
                GameEngineImage* WaeponInterface = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("donkeyui.bmp"));
            }

            {
                GameEngineImage* WaeponInterface = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("cdrom.bmp"));
                WaeponInterface->Cut(1, 25);

            }
        }


        //WindBar UI
        {

            GameEngineImage* WindBarAnim = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("windBar.bmp"));
            WindBarAnim->Cut(5, 4);

            GameEngineImage* WindBarGauge = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("windGauge.bmp"));
            GameEngineImage* WindBarHider = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("windBarHider.bmp"));
        }
        {
            GameEngineImage* PlayerHPbar = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("BottomHPbarB.bmp"));
        }
        {
            GameEngineImage* PlayerHPbar = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("BottomHPbarG.bmp"));
        }
        {
            GameEngineImage* PlayerHPbar = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("BottomHPbarP.bmp"));
        }
        {
            GameEngineImage* PlayerHPbar = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("BottomHPbarR.bmp"));
        }
        {
            GameEngineImage* PlayerHPbar = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("BottomHPbarS.bmp"));
        }
        {
            GameEngineImage* PlayerHPbar = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("BottomHPbarY.bmp"));
        }

        // Time UI
        {

            GameEngineImage* TimeNum = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("TimerNum.bmp"));
            TimeNum->Cut(5, 2);
        }
        {
            GameEngineImage* TimeUI = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("TimerWindowB.bmp"));
        }
        {
            GameEngineImage* TimeUI = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("TimerWindowG.bmp"));
        }
        {
            GameEngineImage* TimeUI = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("TimerWindowP.bmp"));
        }
        {
            GameEngineImage* TimeUI = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("TimerWindowR.bmp"));
        }
        {
            GameEngineImage* TimeUI = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("TimerWindowS.bmp"));
        }
        {
            GameEngineImage* TimeUI = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("TimerWindowY.bmp"));
        }
    }

    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("MapSelect.BMP"));
    }

    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("Teams.BMP"));
    }

    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("Barracks.BMP"));
    }

    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("Option.BMP"));
    }

    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("StartGame.BMP"));
    }
    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("Exit.BMP"));
    }
    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("8436.BMP"));
    }

    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("24226.BMP"));
    }
    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("5618.BMP"));
    }

    // 맵 
    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("LobbyMap_MapBooks.BMP"));
    }
    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("LobbyMap_MapCars.BMP"));
    }
    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("LobbyMap_MapCity.BMP"));
    }
    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("LobbyMap_MapTrain.BMP"));
    }
    // 옵션
    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("weaponoptions.BMP"));
    }
    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("gameoptions.BMP"));
    }
    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("11280.BMP"));
    }
    // 플레이어 
    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("1Up.BMP"));
    }
    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("2Up.BMP"));
    }
    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("3Up.BMP"));
    }
    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("4Up.BMP"));
    }
    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("5Up.BMP"));
    }
    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("6Up.BMP"));
    }
    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("1.BMP"));
    }
    // 턴시간 
    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("000000.BMP"));
    }
    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("000001.BMP"));
    }
    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("000002.BMP"));
    }
    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("000003.BMP"));
    }
    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("000004.BMP"));
    }
    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("000005.BMP"));
    }
    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("000006.BMP"));
    }
    // 라운드 시간 
    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("Round0.BMP"));
    }
    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("Round1.BMP"));
    }
    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("Round2.BMP"));
    }
    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("Round3.BMP"));
    }
    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("Round4.BMP"));
    }
    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("Round5.BMP"));
    }
    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("Round6.BMP"));
    }
    // 이기는 횟수 
    {
        {
            GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("Wins0.BMP"));
        }
        {
            GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("Wins1.BMP"));
        }
        {
            GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("Wins2.BMP"));
        }
        {
            GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("Wins3.BMP"));
        }
        {
            GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("Wins4.BMP"));
        }
        {
            GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("Wins5.BMP"));
        }
        {
            GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("Wins6.BMP"));
        }

    }
    // 웜 선택
    {
        {
            GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("WormSelectOFF.BMP"));
        }
        {
            GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("WormSelectON.BMP"));
        }
        {
            GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("WormSelectRANDOM.BMP"));
        }
    }
    // 웜 체력 
    {
        {
            GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("Hp00.BMP"));
        }
        {
            GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("Hp100.BMP"));
        }
        {
            GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("Hp150.BMP"));
        }
        {
            GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("Hp200.BMP"));
        }
    }
    // 텔레포트 온오브 
    {
        {
            GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("TeleportinOFF.BMP"));
        }
        {
            GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("TeleportinON.BMP"));
        }
    }

    //Select
    {
        {
            GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("6868.BMP"));
        }
    }

	CreateActor<TitleBack>();












}

void TitleLevel::Update(float _DeltaTime)
{

}

void TitleLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}